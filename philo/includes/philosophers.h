/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:28:43 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/28 18:39:39 by jcameira         ###   ########.fr       */
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

typedef struct s_time
{
	time_t		tv_sec;
	suseconds_t	tv_usec;
}				t_time;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				eating;
	int				thinking;
	int				sleeping;
	int				dead;
	pthread_mutex_t	*write;
}				t_philo;

typedef struct s_info
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	t_philo			*philos;
	pthread_t		*philo_tid;
	pthread_t		verify_death;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	write;
	int				time;
}				t_info;

int		argument_number_error(void);
int		inv_argument_error(void);
void	info_init(t_info *info, int argc, char **argv);
void	*philos_mutex_init(t_info *info);
void	philo_info_init(t_info *info, t_philo *philo, int philo_id);
void	*threads_init(t_info *info);
int		isnum(char str);
int		issign(char str);
int		args_check(char **argv);
int		ft_atoi(const char *str);
void	*philo_func(void *philo);

#endif