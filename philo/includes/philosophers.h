/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:28:43 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/01 13:13:16 by jcameira         ###   ########.fr       */
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

# define ARG_NBR_ERROR "Wrong number of arguments.\n"
# define INV_ARG_ERROR "Invalid arguments.\n"

# define FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 4

# define MSG_FORK "%lu %d has taken a fork\n"
# define MSG_EATING "%lu %d is eating\n"
# define MSG_SLEEPING "%lu %d is sleeping\n"
# define MSG_THINKING "%lu %d is thinking\n"
# define MSG_DEAD "%lu %d died\n"

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				eating;
	int				thinking;
	int				sleeping;
	int				dead;
	u_int64_t		current_time;
	struct s_info	*info;
}				t_philo;

typedef struct s_info
{
	u_int64_t		start_time;
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				finish_sim;
	pthread_t		verify_death;
	pthread_mutex_t	write;
	pthread_mutex_t	time;
}				t_info;

int				argument_number_error(void);
int				inv_argument_error(void);
void			info_init(t_info *info, int argc, char **argv);
pthread_mutex_t	*fork_init(t_info *info);
t_philo			*philos_init(t_info *info, pthread_mutex_t *fork_mutex);
void			philo_info_init(t_info *info, t_philo *philo,
				pthread_mutex_t *fork_mutex, int philo_id);
void			*threads_init(t_philo *philos);
int				isnum(char str);
int				issign(char str);
int				args_check(char **argv);
int				ft_atoi(const char *str);
u_int64_t		gettimems(u_int64_t start);
void			*philo_func(void *philo);
void			*death_check(void *philo);
void			terminate_sim(t_philo *philos);

#endif