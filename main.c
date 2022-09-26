/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:53:10 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/26 18:00:06 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_arg(int ac, char *av[], t_main *s)
{
	if (ac == 4)
	{
		s->nb_philo = ft_atoi(av[0]);
		s->nb_forks = ft_atoi(av[0]);
		s->time_to_die = ft_atoi(av[1]);
		s->time_to_eat = ft_atoi(av[2]);
		s->time_to_sleep = ft_atoi(av[3]);
		s->nb_times_ph_eat = 0;
		s->first_time = timestamp();
		pthread_mutex_init(s->print_lock, NULL);
		s->nb_died = 0;
		if (s->nb_philo < 2 || s->time_to_die < 0 || s->time_to_eat < 0
			|| s->time_to_sleep < 0)
			error_code("Arguments are invalid.");
	}
	if (av[4])
	{
		s->nb_times_ph_eat = ft_atoi(av[4]);
		if (s->nb_times_ph_eat <= 0)
			error_code("Argument number 5 must be greater than 0.");
	}
	else
		s->nb_times_ph_eat = -1;
}

int	init_philos(t_main *s)
{
	int	i;

	i = s->nb_philo;
	s->philosopher = malloc(sizeof(t_philo) * s->nb_philo);
	if (!s->philosopher)
		return (EXIT_FAILURE);
	while (i >= 0)
	{
		s->philosopher[i].philo_id = i;
		s->philosopher[i].fork.fork_right = i;
		s->philosopher[i].fork.fork_left = (i + 1) % s->nb_philo;
		s->philosopher[i].eat_times = 0;
		s->philosopher[i].last_meal = 0;
		s->philosopher[i].main = s;
		i--;
		if (pthread_mutex_init(&s->philosopher[i].fork.mut_fork, NULL))
			return (EXIT_FAILURE);
		if (pthread_mutex_init(&s->philosopher[i].eat_lock, NULL))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	state_eating(t_philo *ph)
{
	t_main	*m;

	m = ph->main;
	pthread_mutex_lock(ph->fork.fork_left);
	print_log(timestamp(), ph->philo_id, TAKEN_FORK);
	pthread_mutex_lock(ph->fork.fork_right);
	print_log(timestamp(), ph->philo_id, TAKEN_FORK);
	pthread_mutex_lock(&ph->eat_lock);
	// TO DO EAT | SLEEP | THINK
}

void	*routine(void *param)
{
	t_philo	*ph;
	t_main	*main;

	ph = param;
	main = ph->main;
	while (!main->nb_died)
	{
		state_eating(ph);
	}
	return (NULL);
}

void	init_threads(t_main *s)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = s->philosopher;
	pthread_mutex_init(&s->start_lock, NULL);
	pthread_mutex_lock(&s->start_lock);
	while (i < s->nb_philo)
	{
		if (pthread_create(&s->philosopher[i].thread, NULL, routine, &(ph[i])))
			return (EXIT_FAILURE);
		i++;
	}
	pthread_mutex_unlock(&s->start_lock);
}

int	main(int ac, char *av[])
{
	t_main	shlk;

	if (ac == 6 || ac == 5)
	{
		parse_arg(ac - 1, &av[1], &shlk);
		if (init_philos(&shlk))
			error_code("Failed to create the profiles of the philosophers.");
		init_threads(&shlk);
	}
	else
		error_code("The arguments are invalid(At least 4).");
	return (EXIT_SUCCESS);
}
