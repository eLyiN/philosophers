/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:48:15 by aarribas          #+#    #+#             */
/*   Updated: 2022/10/02 23:37:25 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_main *s)
{
	int	i;

	s->philosophers = (t_philo *)malloc(sizeof(t_philo) * s->nb_philo);
	if (!s->philosophers)
		return (EXIT_FAILURE);
	i = 0;
	while (i < s->nb_philo)
	{
		s->philosophers[i].philo_id = i;
		s->philosophers[i].fork_right = i;
		s->philosophers[i].fork_left = (i + 1) % s->nb_philo;
		s->philosophers[i].eat_times = 0;
		s->philosophers[i].last_meal = 0;
		s->philosophers[i].main = s;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_mutex(t_main *s)
{
	int	i;

	s->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * s->nb_philo);
	if (!s->fork)
		return (error_code(ERROR_10));
	if (pthread_mutex_init(&s->print_lock, NULL))
		return (error_code(ERROR_10));
	i = 0;
	while (i < s->nb_philo)
	{
		if (pthread_mutex_init(&s->fork[i], NULL))
			return (error_code(ERROR_10));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_threads(t_main *s, t_philo *ph)
{
	int	i;

	ph->th_id = (pthread_t *)malloc(sizeof(pthread_t) * s->nb_philo);
	if (!ph->th_id)
		return (error_code(ERROR_11));
	i = 0;
	s->first_time = timestamp();
	while (i < s->nb_philo)
	{
		if (pthread_create(&ph->th_id[i], NULL, routine, &ph[i]))
			return (error_code(ERROR_11));
		usleep(500);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	init_program(t_main *s, t_philo *ph)
{
	int	i;

	i = 0;
	while (1)
	{
		if (s->full_belly >= s->nb_philo)
		{
			usleep(100);
			s->nb_died++;
			return ;
		}
		if (diff_time(ph[i].last_meal, timestamp()) > (long long)s->time_to_die)
		{
			usleep(100);
			print_log(&ph[i], DIED);
			s->nb_died++;
			return ;
		}
		i = (i + 1) % s->nb_philo;
		usleep(500);
	}
}
