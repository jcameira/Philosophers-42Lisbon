/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 19:15:26 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/24 19:22:27 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	info_init(t_info *info,int argc, char **argv)
{
	info->number_of_philo = argv[1];
	info->time_to_die = argv[2];
	info->time_to_eat = argv[3];
	info->time_to_sleep = argv[4];
	if (argc == 6)
		info->times_must_eat = argv[5];
	else
		info->times_must_eat = -1;
}