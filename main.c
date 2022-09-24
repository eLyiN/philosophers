/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:53:10 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/24 13:54:14 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_arg(int ac, char av[], t_main *s)
{
	if (ac == 4)
	{
		s->nb_philo = ft_atoi(av[0]);
		s->nb_forks = ft_atoi(av[0]);
		if (s->nb_philo > MAX_PHILO)
			error_code("Number of philosophers has exceeded the limit (200).");
		s->time_to_die = ft_atoi(av[1]);
		s->time_to_eat = ft_atoi(av[2]);
		s->time_to_sleep = ft_atoi(av[3]);
		s->nb_times_ph_eat = 0;
		if (s->nb_philo < 2 || s->time_to_die < 0 || s->time_to_eat < 0
			|| s->time_to_sleep < 0)
			error_code("Arguments are invalid.");
	}
	if (ac == 5)
	{
		s->nb_times_ph_eat = ft_atoi(av[4]);
		if (s->nb_times_ph_eat <= 0)
			error_code("Argument number 5 must be greater than 0.");
	}
}

void	init_philos(t_main *s)
{
	int	i;

	i = s->nb_philo;
	s->philosopher = malloc(sizeof(t_philo) * s->nb_philo);
	while (i > 0)
	{
		s->philosopher[i].thread = i;
		s->philosopher[i].fork.fork_right = i;
		s->philosopher[i].fork.fork_left = (i + 1) % s->nb_philo;
		s->philosopher[i].eat_times = 0;
		s->philosopher[i].main = s;
		i--;
	}
}

int	main(int ac, char av[])
{
	t_main	shlk;

	if (ac <= 6)
	{
		parse_arg(ac - 1, av[1], &shlk);
		init_philos(&shlk);
	}
	else
		error_code("The arguments exceed those allowed (5).");
	return (EXIT_SUCCESS);
}
