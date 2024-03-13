/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:28:43 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/13 15:52:16 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>

# define ARG_NBR_ERROR "Wrong number of arguments.\n"
# define INV_ARG_ERROR "Invalid arguments.\n"

# define FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4

# define MSG_FORK "%ld %d has taken a fork\n"
# define MSG_EATING "%ld %d is eating\n"
# define MSG_SLEEPING "%ld %d is sleeping\n"
# define MSG_THINKING "%ld %d is thinking\n"
# define MSG_DEAD "%ld %d died\n"

typedef struct s_info
{
	suseconds_t		start_time;
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				philo_satisfied;
	int				finish_sim;
	pthread_t		verify_death;
	pthread_mutex_t	*monitor;
}				t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				times_eaten;
	suseconds_t		last_meal;
	t_info			*info;
}				t_philo;

// Error handling

int				argument_number_error(void);
int				inv_argument_error(void);

// Data initialization

void			info_init(t_info *info, int argc, char **argv);
pthread_mutex_t	*fork_init(t_info *info);
t_philo			*philos_init(t_info *info, pthread_mutex_t *fork_mutex);
void			philo_info_init(t_info *info, t_philo *philo,
					pthread_mutex_t *fork_mutex, int philo_id);
void			*threads_init(t_philo *philos);

// Cleanup

void			clean_sim(pthread_mutex_t *fork_mutex, t_philo *philos);

// Main routine

void			*philo_func(void *philo);
void			*single_philo(t_philo *philo);
void			grab_forks(t_philo *philo);
void			eating_sleeping(t_philo *philo);
void			drop_forks(t_philo *philo);

// Simulation termination checker

void			*death_check(void *philo);
void			eat_check(t_philo *philos);
void			*finish_sim(t_philo *philos);

// Utility functions

int				args_check(char **argv);
int				ft_atoi(const char *str);
void			log_state(int state, t_philo *philo);
void			in_action(t_philo *philo, suseconds_t time_to_wait);
suseconds_t		gettimems(void);

#endif