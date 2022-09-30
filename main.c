/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:53:10 by aarribas          #+#    #+#             */
/*   Updated: 2022/10/01 00:25:45 by aarribas         ###   ########.fr       */
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
		s->times_must_eat = ft_atoi(av[4]);
		if (s->times_must_eat <= 0)
			error_code("Argument number 5 must be greater than 0.");
	}
	else
		s->times_must_eat = -1;
	s->nb_died = 0;
}

void	terminate_mutex(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->main->nb_philo)
	{
		pthread_mutex_destroy(p[i].mut_fork);
		i++;
	}
}

void	death_checker(t_main *s, t_philo *ph)
{
	int	i;

	i = 0;
	while (1)
	{
		if (diff_time(ph[i].last_meal, timestamp()) >= s->time_to_die)
		{
			usleep(100);
			print_log(&ph[i], DIED);
			terminate_mutex(ph);
			free(ph);
			free(ph->mut_fork);
			free(s);
			return ;
		}
		i++;
		usleep(500);
	}
}

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

int	main(int ac, char *av[])
{
	t_main		*shlk;
	t_philo		*ph;
	pthread_t	*th;

	if (ac == 6 || ac == 5)
	{
		if (check_arg(&av[1]))
			error_code("Only accept numbers as argument.");
		shlk = (t_main *)malloc(sizeof(t_main));
		parse_arg(&av[1], shlk);
		ph = (t_philo *)malloc(sizeof(t_philo) * shlk->nb_philo);
		if (init_philos(shlk, ph))
			error_code("Failed to create the profiles of the philosophers.");
		init_mutex(shlk, ph);
		th = (pthread_t *)malloc(sizeof(pthread_t) * shlk->nb_philo);
		if (init_threads(shlk, th, ph))
			error_code("Failed to create the threads of the philosophers.");
		death_checker(shlk, ph);
		free(th);
		free(shlk);
	}
	else
		error_code("At least 4 or 5 arguments are required.");
	return (EXIT_SUCCESS);
}
