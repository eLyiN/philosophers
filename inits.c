/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:48:15 by aarribas          #+#    #+#             */
/*   Updated: 2022/10/01 00:28:36 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_main *s, t_philo *p)
{
	int	i;

	i = 0;
	while (i < s->nb_philo)
	{
		p[i].philo_id = i;
		p[i].fork_right = i;
		p[i].fork_left = (i + 1) % s->nb_philo;
		p[i].eat_times = 0;
		p[i].last_meal = 0;
		p[i].main = s;
		i++;
	}
	return (EXIT_SUCCESS);
}

void	init_mutex(t_main *s, t_philo *ph)
{
	int				i;
	pthread_mutex_t	*mut;

	mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * s->nb_philo);
	if (!mut)
		error_code("Fail on memory mutex allocation.");
	pthread_mutex_init(&s->print_lock, NULL);
	i = 0;
	while (i < s->nb_philo)
	{
		ph[i].mut_fork = &mut[i];
		if (pthread_mutex_init(&mut[i], NULL))
			error_code("Fail on mutex initiation.");
		i++;
	}
}

int	init_threads(t_main *s, pthread_t *th, t_philo *ph)
{
	int	i;

	i = 0;
	s->first_time = timestamp();
	while (i < s->nb_philo)
	{
		if (pthread_create(&th[i], NULL, routine, &(ph[i])))
			return (EXIT_FAILURE);
		ph->last_meal = timestamp();
		i++;
	}
	return (EXIT_SUCCESS);
}
