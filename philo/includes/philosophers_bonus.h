/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:50:52 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/13 02:55:44 by jcameira         ###   ########.fr       */
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
}				t_info;

// Error handling

int				argument_number_error(void);
int				inv_argument_error(void);

#endif