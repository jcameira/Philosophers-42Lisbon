/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:58:08 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/13 02:58:46 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	info_init(t_info *info, int argc, char **argv)
{
	info->number_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->times_must_eat = ft_atoi(argv[5]);
	else
		info->times_must_eat = -1;
	info->philo_satisfied = 0;
	info->finish_sim = 0;
}

