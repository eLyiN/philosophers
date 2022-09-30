/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:50:17 by aarribas          #+#    #+#             */
/*   Updated: 2022/10/01 00:29:19 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	state_eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->mut_fork[ph->fork_left]);
	print_log(ph, TAKEN_FORK);
	printf("FORK ID: %d\n", ph->fork_left);
	pthread_mutex_lock(&ph->mut_fork[ph->fork_right]);
	printf("FORK ID: %d\n", ph->fork_right);
	print_log(ph, TAKEN_FORK);
	print_log(ph, EATING);
	ph->eat_times++;
	usleep(ph->main->time_to_eat * 1000);
	ph->last_meal = timestamp();
	pthread_mutex_unlock(&ph->mut_fork[ph->fork_left]);
	pthread_mutex_unlock(&ph->mut_fork[ph->fork_right]);
}

void	state_sleeping(t_philo *ph)
{
	t_main	*m;

	m = ph->main;
	print_log(ph, SLEEPING);
	usleep(m->time_to_sleep * 1000);
}

void	*routine(void *param)
{
	t_philo	*ph;

	ph = (t_philo *)param;
	while (1)
	{
		state_eating(ph);
		state_sleeping(ph);
		print_log(ph, THINKING);
	}
	return (NULL);
}
