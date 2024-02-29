/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:37:49 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/29 22:30:23 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*death_check(void *philo)
{
	t_philo	*philos;
	int	i;

	philos = (t_philo *)philo;
	while (!philos[0].info->finish_sim)
	{
		i = -1;
		while (++i < philos[0].info->number_of_philo)
		{
			pthread_mutex_lock(&philos[i].info->time);
			//printf("current_time: %lu\n", philos[i].current_time);
			//printf("current_time: %lu\n", gettimems(philos[i].current_time));
			//printf("current_time: %lu\n", philos[i].current_time);
			if (gettimems(philos[i].current_time) > (u_int64_t)philos[i].info->time_to_die)
			{
				//printf("current_time: %lu\n", philos[i].current_time);
				philos[i].info->finish_sim = 1;
				pthread_mutex_lock(&philos[i].info->write);
				printf(MSG_DEAD, gettimems(philos[i].info->start_time), philos[i].id);
				pthread_mutex_unlock(&philos[i].info->write);
				exit(1);
			}
			pthread_mutex_unlock(&philos[i].info->time);
		}
	}
	return (philo);
}

void	change_state(int state, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->write);
	if (state == FORK)
		printf(MSG_FORK, gettimems(philo->info->start_time), philo->id);
	else if (state == EATING)
		printf(MSG_EATING, gettimems(philo->info->start_time), philo->id);
	else if (state == SLEEPING)
		printf(MSG_SLEEPING, gettimems(philo->info->start_time), philo->id);
	else if (state == THINKING)
		printf(MSG_THINKING, gettimems(philo->info->start_time), philo->id);
	else if (state == DEAD)
		printf(MSG_DEAD, gettimems(philo->info->start_time), philo->id);
	pthread_mutex_unlock(&philo->info->write);
}

void	sleeping(t_philo *philo)
{
	change_state(SLEEPING, philo);
	usleep(philo->info->time_to_sleep * 1000);
	change_state(THINKING, philo);
}

void	eating(t_philo *philo)
{
	struct timeval	start;
	
	pthread_mutex_lock(philo->l_fork);
	change_state(FORK, philo);
	pthread_mutex_lock(philo->r_fork);
	change_state(FORK, philo);
	change_state(EATING, philo);
	pthread_mutex_lock(&philo->info->time);
	gettimeofday(&start, NULL);
	philo->current_time = (start.tv_sec * 1000000) + start.tv_usec;
	pthread_mutex_unlock(&philo->info->time);
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	usleep(100);
}

void	*philo_func(void *philo)
{
	while (1)
	{
		eating((t_philo *)philo);
		sleeping((t_philo *)philo);
	}
	return (NULL);
}