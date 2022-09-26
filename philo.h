/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:51:21 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/26 17:45:05 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILO 200

typedef enum e_states
{
	EATING,
	THINKING,
	SLEEPING,
	TAKEN_FORK,
	DIED,
}					t_states;

typedef struct s_fork
{
	int				fork_left;
	int				fork_right;
	pthread_mutex_t	mut_fork;
}					t_fork;

typedef struct s_philo
{
	int				philo_id;
	int				eat_times;
	long long		last_meal;
	t_states		states;
	pthread_t		thread;
	t_fork			fork;
	pthread_mutex_t	eat_lock;
	struct s_main	*main;
}					t_philo;

typedef struct s_main
{
	int				nb_philo;
	int				nb_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_ph_eat;
	int				nb_died;
	long long		first_time;
	t_philo			*philosopher;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	print_lock;
	pthread
}					t_main;

// Utils

int					ft_atoi(const char *str);
void				error_code(char *str);
long long			timestamp(void);
void				print_log(t_philo *ph, long long timestamp, t_states state);

#endif
