/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:53:10 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/27 21:26:04 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_arg(char *av[], t_main *s)
{
	s->nb_philo = ft_atoi(av[0]);
	if (s->nb_philo < 1)
		error_code("Argument number 1 must be greater than 1.");
	s->time_to_die = ft_atoi(av[1]);
	if (s->time_to_die < 0)
		error_code("Argument number 2 must be greater than 0.");
	s->time_to_eat = ft_atoi(av[2]);
	if (s->time_to_eat < 0)
		error_code("Argument number 3 must be greater than 0.");
	s->time_to_sleep = ft_atoi(av[3]);
	if (s->time_to_sleep < 0)
		error_code("Argument number 4 must be greater than 0.");
	if (av[4])
	{
		s->nb_times_ph_eat = ft_atoi(av[4]);
		if (s->nb_times_ph_eat <= 0)
			error_code("Argument number 5 must be greater than 0.");
	}
	else
		s->nb_times_ph_eat = -1;
	s->nb_died = 0;
}

int	init_philos(t_main *s)
{
	int	i;

	i = 1;
	while (i <= s->nb_philo)
	{
		s->philosopher[i].philo_id = i;
		s->philosopher[i].fork.fork_right = i;
		s->philosopher[i].fork.fork_left = (i + 1) % s->nb_philo;
		s->philosopher[i].eat_times = 0;
		s->philosopher[i].last_meal = 0;
		s->philosopher[i].main = s;
		pthread_mutex_init(&s->mut_fork[i], NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	state_eating(t_philo *ph)
{
	t_main		*m;
	long long	eat_start;
	long long	eat_finish;

	m = ph->main;
	pthread_mutex_lock(&m->mut_fork[ph->fork.fork_left]);
	print_log(ph, TAKEN_FORK);
	pthread_mutex_lock(&m->mut_fork[ph->fork.fork_right]);
	print_log(ph, TAKEN_FORK);
	pthread_mutex_lock(&m->eating);
	print_log(ph, EATING);
	ph->eat_times++;
	eat_start = timestamp();
	while (m->time_to_eat >= eat_finish)
		eat_finish = diff_time(eat_start, timestamp());
	ph->last_meal = timestamp();
	pthread_mutex_unlock(&m->eating);
	pthread_mutex_unlock(&m->mut_fork[ph->fork.fork_left]);
	pthread_mutex_unlock(&m->mut_fork[ph->fork.fork_right]);
}

void	state_sleeping(t_philo *ph)
{
	long long	sleep_start;
	long long	sleep_finish;

	print_log(ph, SLEEPING);
	sleep_start = timestamp();
	while (sleep_finish >= ph->main->time_to_sleep)
		sleep_finish = timestamp() - sleep_start;
	if (sleep_finish >= ph->main->time_to_die)
		ph->main->nb_died++;
}

void	*routine(void *param)
{
	t_philo	*ph;
	t_main	*main;

	ph = (t_philo *)param;
	main = ph->main;
	while (!main->nb_died)
	{
		state_eating(ph);
		if (ph->last_meal > main->time_to_die)
			main->nb_died++;
		state_sleeping(ph);
		print_log(ph, THINKING);
		main->nb_died++;
	}
	return (NULL);
}
void	init_mutex(t_main *s)
{
	pthread_mutex_init(&s->print_lock, NULL);
	pthread_mutex_init(&s->start_lock, NULL);
	pthread_mutex_init(&s->eating, NULL);
	pthread_mutex_lock(&s->start_lock);
}

int	init_threads(t_main *s)
{
	int		i;
	t_philo	*ph;

	i = 1;
	ph = s->philosopher;
	s->first_time = timestamp();
	pthread_mutex_unlock(&s->start_lock);
	while (i <= s->nb_philo)
	{
		if (pthread_create(&s->philosopher[i].thread, NULL, routine, &(ph[i])))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char *av[])
{
	t_main	shlk;
	int		i;

	if (ac == 6 || ac == 5)
	{
		parse_arg(&av[1], &shlk);
		printf("nb_philo:%d\n", shlk.nb_philo);
		printf("time_to_die:%d\n", shlk.time_to_die);
		printf("time_to_sleep:%d\n", shlk.time_to_sleep);
		printf("time_to_eat:%d\n", shlk.time_to_eat);
		if (init_philos(&shlk))
			error_code("Failed to create the profiles of the philosophers.");
		i = 1;
		while (i <= shlk.nb_philo)
		{
			printf("philo_id: %d\n", shlk.philosopher[i].philo_id);
			printf("eat_times: %d\n", shlk.philosopher[i].eat_times);
			printf("last_meal: %lld\n", shlk.philosopher[i].last_meal);
			printf("fork_left: %d\n", shlk.philosopher[i].fork.fork_left);
			printf("fork_right: %d\n", shlk.philosopher[i].fork.fork_right);
			i++;
		}
		init_mutex(&shlk);
		if (init_threads(&shlk))
			error_code("Failed to create the threads of the philosophers.");
	}
	else
		error_code("The arguments are invalid(At least 4).");
	return (EXIT_SUCCESS);
}
