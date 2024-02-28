/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:37:49 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/28 19:33:15 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*philo_func(void *philo)
{
	while (1)
	{
		eat((t_philo *)philo);
		sleep((t_philo *)philo);
	}
	return (NULL);
}