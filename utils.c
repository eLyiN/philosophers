/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:57:38 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/26 17:42:33 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signo;
	int	nbr;

	i = 0;
	signo = 1;
	nbr = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signo = -1;
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
		return (-1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		nbr = nbr * 10 + (str[i++] - '0');
	return (signo * nbr);
}

void	error_code(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(STDOUT_FILENO, "Error\n", 7);
	write(STDOUT_FILENO, str, i);
	write(STDOUT_FILENO, "\n", 1);
}

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_log(t_philo *ph, long long timestamp, t_states state)
{
	pthread_mutex_lock(&ph->main->print_lock);
	if (state == TAKEN_FORK)
		printf("%lld %d has taken a fork\n", timestamp, &ph->philo_id);
	else if (state == DIED)
		printf("%lld %d died\n", timestamp, &ph->philo_id);
	else if (state == SLEEPING)
		printf("%lld %d is sleeping\n", timestamp, &ph->philo_id);
	else if (state == EATING)
		printf("%lld %d is eating\n", timestamp, &ph->philo_id);
	else if (state == THINKING)
		printf("%lld %d is thinking\n", timestamp, &ph->philo_id);
	pthread_mutex_lock(&ph->main->print_lock);
}
