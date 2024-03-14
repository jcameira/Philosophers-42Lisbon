/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 04:56:10 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/14 04:58:58 by jcameira         ###   ########.fr       */
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
