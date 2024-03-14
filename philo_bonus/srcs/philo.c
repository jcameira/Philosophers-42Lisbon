/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 03:52:40 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/14 21:16:57 by jcameira         ###   ########.fr       */
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
	sem_wait(philo->info->sem_death);
	log_state(EATING, philo);
	philo->last_meal = gettimems();
	sem_post(philo->info->sem_death);
	usleep(philo->info->time_to_eat * 1000);
	drop_forks(philo);
	philo->times_eaten++;
	if (philo->info->times_must_eat > -1)
		if (philo->times_eaten >= philo->info->times_must_eat)
			sem_post(philo->info->sem_eat);
	log_state(SLEEPING, philo);
	usleep(philo->info->time_to_sleep * 1000);
	log_state(THINKING, philo);
}

void	philo_func(t_philo *philo)
{
	t_philo	*philos;

	philos = (t_philo *)philo;
	philos->last_meal = gettimems();
	while (1)
		eating_sleeping(philos);
}
