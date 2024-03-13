/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:50:52 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/13 15:57:02 by jcameira         ###   ########.fr       */
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

# define SEM_FORKS "/forks"
# define SEM_PRINT "/print"
# define SEM_EAT "/eat"
# define SEM_DEATH "/death"

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
	suseconds_t	start_time;
	int			number_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_must_eat;
	int			philo_satisfied;
	int			finish_sim;
	sem_t		*sem_forks;
	sem_t		*sem_print;
	sem_t		*sem_eat;
	sem_t		*sem_death;
}				t_info;

typedef struct s_philo
{
	int			id;
	pid_t		pid;
	int			times_eaten;
	suseconds_t	last_meal;
	t_info		*info;
}				t_philo;

// Error handling

int		argument_number_error(void);
int		inv_argument_error(void);

// Data initialization

void	info_init(t_info *info, int argc, char **argv);
t_philo	*philo_init(t_info *info);
void	processes_init(t_philo *philos);

// Utility functions

int		args_check(char **argv);

#endif