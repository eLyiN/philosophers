/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/09/23 18:57:38 by aarribas          #+#    #+#             */
/*   Updated: 2022/10/02 23:37:26 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int i;
	int signo;
	int nbr;

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

int	error_code(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	write(STDOUT_FILENO, "Error\n", 7);
	write(STDOUT_FILENO, str, i);
	write(STDOUT_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}

long long	timestamp(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	diff_time(long long t_past, long long t_present)
{
	return (t_present - t_past);
}

void	print_log(t_philo *ph, t_states state)
{
	long long time_calc;

	time_calc = timestamp() - ph->main->first_time;
	pthread_mutex_lock(&ph->main->print_lock);
	if (!ph->main->nb_died)
	{
		if (state == TAKEN_FORK && !ph->main->nb_died)
			printf("%lld %d has taken a fork\n", time_calc, ph->philo_id + 1);
		else if (state == DIED)
			printf("%lld %d died\n", time_calc, ph->philo_id + 1);
		else if (state == SLEEPING && !ph->main->nb_died)
			printf("%lld %d is sleeping\n", time_calc, ph->philo_id + 1);
		else if (state == EATING && !ph->main->nb_died)
			printf("%lld %d is eating\n", time_calc, ph->philo_id + 1);
		else if (state == THINKING && !ph->main->nb_died)
			printf("%lld %d is thinking\n", time_calc, ph->philo_id + 1);
	}
	pthread_mutex_unlock(&ph->main->print_lock);
	return ;
}
