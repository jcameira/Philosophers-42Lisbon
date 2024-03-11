/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:37:49 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/11 18:57:01 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	eat_check(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos[0].info->number_of_philo)
	{
		pthread_mutex_lock(&philos[i].info->eat);
		if (philos[i].times_eaten >= philos->info->times_must_eat)
			philos->info->philo_satisfied++;
		pthread_mutex_unlock(&philos[i].info->eat);
	}
	if (philos[0].info->philo_satisfied == philos[0].info->number_of_philo)
		philos->info->finish_sim = 1;
	else
		philos->info->philo_satisfied = 0;
}

void	*death_check(void *philo)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)philo;
	while (!philos->info->finish_sim)
	{
		i = -1;
		while (++i < philos->info->number_of_philo)
		{
			pthread_mutex_lock(&philos->info->time);
			if (gettimems(philos[i].current_time) >= (u_int64_t)philos[i].info->time_to_die)
			{
				log_state(DEAD, &philos[i]);
				philos->info->finish_sim = 1;
				pthread_mutex_unlock(&philos->info->time);
				return (philo);
			}
			pthread_mutex_unlock(&philos->info->time);
		}
		if (philos[0].info->times_must_eat > -1)
			eat_check(philos);
	}
	return (philo);
}

void	log_state(int state, t_philo *philo)
{
	const char	*messages[5] = {MSG_FORK, MSG_EATING, MSG_SLEEPING,
		MSG_THINKING, MSG_DEAD};

	if (!philo->info->finish_sim)
	{
		pthread_mutex_lock(&philo->info->write);
		printf(messages[state], gettimems(philo->info->start_time), philo->id);
		pthread_mutex_unlock(&philo->info->write);
	}
}

void	sleeping(t_philo *philo)
{
	log_state(SLEEPING, philo);
	usleep(philo->info->time_to_sleep * 1000);
	log_state(THINKING, philo);
}

void	grab_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		log_state(FORK, philo);
		pthread_mutex_lock(philo->r_fork);
		log_state(FORK, philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		log_state(FORK, philo);
		pthread_mutex_lock(philo->l_fork);
		log_state(FORK, philo);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

void	eating(t_philo *philo)
{
	struct timeval	start;

	grab_forks(philo);
	if (philo->info->finish_sim)
	{
		drop_forks(philo);
		return ;
	}
	log_state(EATING, philo);
	pthread_mutex_lock(&philo->info->time);
	gettimeofday(&start, NULL);
	philo->current_time = (start.tv_sec * 1000000) + start.tv_usec;
	pthread_mutex_unlock(&philo->info->time);
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_lock(&philo->info->eat);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->info->eat);
	drop_forks(philo);
}

void	*philo_func(void *philo)
{
	t_philo	*philos;

	philos = (t_philo *)philo;
	pthread_mutex_lock(&philos->info->start);
	pthread_mutex_unlock(&philos->info->start);
	while (1)
	{
		if (philos->info->finish_sim)
			return (philos);
		if (philos->info->number_of_philo == 1)
		{
			log_state(FORK, philos);
			return (philo);
		}
		eating(philos);
		if (philos->info->finish_sim)
			return (philos);
		sleeping(philos);
	}
	return (philo);
}
