/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 03:52:40 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/23 19:46:19 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	grab_forks(t_philo *philo)
{
	sem_wait(philo->info->sem_forks);
	log_state(FORK, philo);
	sem_wait(philo->info->sem_forks);
	log_state(FORK, philo);
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->info->sem_forks);
	sem_post(philo->info->sem_forks);
}

void	eating_sleeping(t_philo *philo)
{
	grab_forks(philo);
	log_state(EATING, philo);
	pthread_mutex_lock(philo->monitor_mutex);
	philo->last_meal = gettimems();
	pthread_mutex_unlock(philo->monitor_mutex);
	in_action(philo->info->time_to_eat);
	philo->times_eaten++;
	if (philo->info->times_must_eat > -1)
		if (philo->times_eaten >= philo->info->times_must_eat)
			sem_post(philo->info->sem_eat);
	drop_forks(philo);
	log_state(SLEEPING, philo);
	in_action(philo->info->time_to_sleep);
	log_state(THINKING, philo);
}

void	single_philo(t_philo *philo)
{
	log_state(FORK, philo);
	in_action(philo->info->time_to_die);
}

void	philo_func(t_philo *philo)
{
	t_philo	*philos;

	philos = (t_philo *)philo;
	sem_wait(philos->info->sem_start);
	philos->info->start_time = gettimems();
	sem_post(philos->info->sem_start);
	pthread_mutex_lock(philos->monitor_mutex);
	philos->last_meal = gettimems();
	pthread_mutex_unlock(philos->monitor_mutex);
	if (philos->info->number_of_philo == 1)
		single_philo(philos);
	if (philos->id % 2 == 0)
		usleep(philos->info->number_of_philo * 10000);
	while (1)
	{
		usleep(100);
		eating_sleeping(philos);
	}
}
