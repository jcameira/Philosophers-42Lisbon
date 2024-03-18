/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 03:52:40 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/18 20:04:49 by jcameira         ###   ########.fr       */
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
	in_action(philo->info->time_to_eat);
	drop_forks(philo);
	philo->times_eaten++;
	if (philo->info->times_must_eat > -1)
		if (philo->times_eaten >= philo->info->times_must_eat)
			sem_post(philo->info->sem_eat);
	log_state(SLEEPING, philo);
	in_action(philo->info->time_to_sleep);
	log_state(THINKING, philo);
}

void	philo_func(t_philo *philo)
{
	t_philo	*philos;

	philos = (t_philo *)philo;
	philos->last_meal = gettimems();
	while (1)
	{
		usleep(100);
		sem_wait(philos->info->sem_death);
		if (philos->info->finish_sim)
		{
			sem_post(philos->info->sem_death);
			clean_sim(philo);
			exit (0);
		}
		sem_post(philos->info->sem_death);
		eating_sleeping(philos);
	}
}
