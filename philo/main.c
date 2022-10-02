/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:53:10 by aarribas          #+#    #+#             */
/*   Updated: 2022/10/02 23:01:32 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] >= '0' && av[i][j] <= '9')
				j++;
			else
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	parse_arg(char *av[], t_main *s)
{
	s->nb_philo = ft_atoi(av[0]);
	if (s->nb_philo < 1)
		return (error_code(ERROR_5));
	s->time_to_die = ft_atoi(av[1]);
	if (s->time_to_die < 0)
		return (error_code(ERROR_6));
	s->time_to_eat = ft_atoi(av[2]);
	if (s->time_to_eat < 0)
		return (error_code(ERROR_7));
	s->time_to_sleep = ft_atoi(av[3]);
	if (s->time_to_sleep < 0)
		return (error_code(ERROR_8));
	if (av[4])
	{
		s->times_must_eat = ft_atoi(av[4]);
		if (s->times_must_eat <= 0)
			return (error_code(ERROR_9));
	}
	else
		s->times_must_eat = -1;
	s->nb_died = 0;
	return (EXIT_SUCCESS);
}

void	*routine(void *param)
{
	t_philo	*ph;

	ph = (t_philo *)param;
	if (ph->philo_id % 2)
		usleep(1000);
	ph->last_meal = timestamp();
	while (ph->main->nb_died == 0)
	{
		pthread_mutex_lock(&ph->main->fork[ph->fork_left]);
		print_log(ph, TAKEN_FORK);
		pthread_mutex_lock(&ph->main->fork[ph->fork_right]);
		print_log(ph, TAKEN_FORK);
		print_log(ph, EATING);
		ph->eat_times++;
		if (ph->eat_times >= ph->main->times_must_eat)
			ph->main->full_belly++;
		ph->last_meal = timestamp();
		usleep(ph->main->time_to_eat * 1000);
		pthread_mutex_unlock(&ph->main->fork[ph->fork_left]);
		pthread_mutex_unlock(&ph->main->fork[ph->fork_right]);
		print_log(ph, SLEEPING);
		usleep(ph->main->time_to_sleep * 1000);
		print_log(ph, THINKING);
	}
	return (NULL);
}

void	exit_program(t_main *s)
{
	int	i;

	i = -1;
	while (++i < s->nb_philo)
	{
		pthread_join(s->philosophers->th_id[i], NULL);
		pthread_mutex_destroy(&s->fork[i]);
	}
	pthread_mutex_destroy(&s->print_lock);
	free(s->philosophers->th_id);
	free(s->philosophers);
	return ;
}

int	main(int ac, char *av[])
{
	t_main	*shlk;

	if (ac > 6 || ac < 5)
		return (error_code(ERROR_1));
	if (check_arg(&av[1]))
		return (error_code(ERROR_2));
	shlk = (t_main *)malloc(sizeof(t_main));
	if (!shlk)
		return (EXIT_FAILURE);
	parse_arg(&av[1], shlk);
	if (init_philos(shlk))
		return (error_code(ERROR_3));
	init_mutex(shlk);
	if (init_threads(shlk, shlk->philosophers))
		return (error_code(ERROR_4));
	init_program(shlk, shlk->philosophers);
	exit_program(shlk);
	return (EXIT_SUCCESS);
}
