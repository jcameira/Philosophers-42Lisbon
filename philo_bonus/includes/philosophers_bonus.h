/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:50:52 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/23 14:10:34 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

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

# define SEM_START "/start"
# define SEM_FORKS "/forks"
# define SEM_PRINT "/print"
# define SEM_EAT "/eat"
# define SEM_DEATH "/death"

# define FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define SATISFIED 4
# define DEAD 5

# define ANY -1

# define SIM_START "---------------------------------------\n\
|   \033[35mTIME\033[0m   | \033[35mPHILO\033[0m |      \033[35mEVENT\033[0m       |\n\
---------------------------------------\n"

# define SIM_END "---------------------------------------\n"

# define MSG_FORK "|\033[36m%10ld\033[0m|%4d   | \
\033[33mhas taken a fork\033[0m |\n"
# define MSG_EATING "|\033[36m%10ld\033[0m|%4d   |    \
\033[33mis eating\033[0m     |\n"
# define MSG_SLEEPING "|\033[36m%10ld\033[0m|%4d   |   \
\033[33mis sleeping\033[0m    |\n"
# define MSG_THINKING "|\033[36m%10ld\033[0m|%4d   |   \
\033[33mis thinking\033[0m    |\n"
# define MSG_SATISFIED "|\033[36m%10ld\033[0m|   \
\033[32mall philos satisfied\033[0m   |\n"
# define MSG_DEAD "|\033[36m%10ld\033[0m|%4d   |       \
\033[31mdied\033[0m       |\n"

typedef struct s_info
{
	suseconds_t	start_time;
	int			number_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_must_eat;
	int			philo_satisfied;
	sem_t		*sem_start;
	sem_t		*sem_forks;
	sem_t		*sem_print;
	sem_t		*sem_eat;
	sem_t		*sem_death;
	pthread_t	verify_satisfied;
	pthread_t	kill_philos;
}				t_info;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	pthread_t		monitor;
	pthread_mutex_t	*monitor_mutex;
	int				times_eaten;
	suseconds_t		last_meal;
	t_info			*info;
}				t_philo;

// Error handling

int			argument_number_error(void);
int			inv_argument_error(void);

// Data initialization

void		info_init(t_info *info, int argc, char **argv);
t_philo		*philo_init(t_info *info);
void		processes_init(t_philo *philos);

// Cleanup

void		checking_threads(t_philo *philos);
void		kill_philos(t_philo *philos);
void		clean_sim(t_philo *philos);

// Main routine

void		philo_func(t_philo *philo);
void		grab_forks(t_philo *philo);
void		eating_sleeping(t_philo *philo);
void		drop_forks(t_philo *philo);

// Simulation termination checker

void		*kill_func(void *philo);
void		*meals_func(void *philo);
void		*monitor_func(void *philo);

// Utility functions

int			args_check(char **argv);
int			ft_atoi(const char *str);
void		log_state(int state, t_philo *philo);
void		in_action(suseconds_t time_to_wait);
suseconds_t	gettimems(void);

#endif