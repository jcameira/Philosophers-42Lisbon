/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_end_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 03:53:33 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/21 16:22:08 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	*kill_func(void *philo)
{
	t_philo	*philos;

	philos = (t_philo *)philo;
	sem_wait(philos->info->sem_death);
	if (philos->info->times_must_eat > -1)
		usleep(1000);
	kill_philos(philos);
	return (NULL);
}

void	*meals_func(void *philo)
{
	t_philo	*philos;
	int		satisfied;

	philos = (t_philo *)philo;
	satisfied = -1;
	while (++satisfied < philos->info->number_of_philo)
		sem_wait(philos->info->sem_eat);
	sem_post(philos->info->sem_death);
	return (NULL);
}

void	*monitor_func(void *philo)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(philos->monitor_mutex);
		if (gettimems() - philos->last_meal
			>= (suseconds_t)philos->info->time_to_die)
		{
			pthread_mutex_unlock(philos->monitor_mutex);
			log_state(DEAD, philos);
			sem_wait(philos->info->sem_print);
			sem_post(philos->info->sem_death);
			if (philos->info->times_must_eat > -1)
			{
				i = -1;
				while (++i < philos->info->number_of_philo)
					sem_post(philos->info->sem_eat);
			}
			return (NULL);
		}
		pthread_mutex_unlock(philos->monitor_mutex);
		usleep(100);
	}
}
