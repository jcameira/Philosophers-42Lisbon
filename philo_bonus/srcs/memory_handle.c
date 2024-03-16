/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 04:56:10 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/16 21:49:30 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	kill_philos(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->info->number_of_philo)
		kill(philos[i].pid, SIGINT);
}

void	clean_sim(t_philo *philos)
{
	if (philos->info->times_must_eat > -1)
		sem_post(philos->info->sem_eat);
	sem_close(philos->info->sem_forks);
	sem_close(philos->info->sem_print);
	sem_close(philos->info->sem_eat);
	sem_close(philos->info->sem_death);
	free(philos->info);
	free(philos);
}
