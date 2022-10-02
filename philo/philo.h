/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:51:21 by aarribas          #+#    #+#             */
/*   Updated: 2022/10/02 21:56:47 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "error_macro.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_states
{
	EATING,
	THINKING,
	SLEEPING,
	TAKEN_FORK,
	DIED,
}					t_states;

typedef struct s_philo
{
	int				philo_id;
	int				eat_times;
	long long		last_meal;
	int				fork_left;
	int				fork_right;
	pthread_t		*th_id;
	struct s_main	*main;
}					t_philo;

typedef struct s_main
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				full_belly;
	int				nb_died;
	long long		first_time;
	t_philo			*philosophers;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_lock;
}					t_main;

// Utils

int					ft_atoi(const char *str);
int					error_code(char *str);
long long			timestamp(void);
void				print_log(t_philo *ph, t_states state);
long long			diff_time(long long t_past, long long t_present);

// Inits.c

int					init_threads(t_main *s, t_philo *ph);
int					init_mutex(t_main *s);
int					init_philos(t_main *s);
void				init_program(t_main *s, t_philo *ph);

// Routine.c

void				*routine(void *param);

#endif
