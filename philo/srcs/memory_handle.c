/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:29:36 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/01 12:43:00 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	terminate_sim(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos[0].info->number_of_philo)
	{
		if (philos[i].l_fork)
		{
			pthread_mutex_destroy(philos[i].l_fork);
			philos[i].l_fork = NULL;
		}
		if (philos[i].r_fork)
		{
			pthread_mutex_destroy(philos[i].r_fork);
			philos[i].r_fork = NULL;
		}
	}
}
