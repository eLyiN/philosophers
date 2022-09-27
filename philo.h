/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:51:21 by aarribas          #+#    #+#             */
/*   Updated: 2022/09/27 21:26:08 by aarribas         ###   ########.fr       */
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

}					t_fork;

typedef struct s_philo
{
	int				philo_id;
	int				eat_times;
	long long		last_meal;
	t_states		states;
	pthread_t		thread;
	t_fork			fork;
	struct s_main	*main;
}					t_philo;

typedef struct s_main
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_times_ph_eat;
	int				nb_died;
	long long		first_time;
	t_philo			philosopher[MAX_PHILO];
	pthread_mutex_t	mut_fork[MAX_PHILO];
	pthread_mutex_t	eating;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	print_lock;
}					t_main;

// Utils

int					ft_atoi(const char *str);
void				error_code(char *str);
long long			timestamp(void);
void				print_log(t_philo *ph, t_states state);
long long			diff_time(long long t_past, long long t_present);

#endif
