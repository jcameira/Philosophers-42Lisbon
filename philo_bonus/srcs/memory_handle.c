/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 04:56:10 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/23 19:57:49 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	kill_philos(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->info->number_of_philo)
		kill(philos[i].pid, SIGKILL);
}

void	clean_sim(t_philo *philos)
{
	int	i;

	sem_close(philos->info->sem_start);
	sem_close(philos->info->sem_forks);
	sem_close(philos->info->sem_print);
	sem_close(philos->info->sem_eat);
	sem_close(philos->info->sem_death);
	i = -1;
	while (++i < philos->info->number_of_philo)
		free(philos[i].monitor_mutex);
	free(philos->info);
	free(philos);
}
