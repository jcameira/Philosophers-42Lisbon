/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:39:02 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/28 12:08:09 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	main(int argc, char **argv)
{
	t_info	*info;
	int		i;

	if (argc < 5 || argc > 6)
		return (argument_number_error());
	if (!args_check(argv))
		return (inv_argument_error());
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
	info_init(info, argc, argv);
	philos_mutex_init(info);
	threads_init(info);
	i = -1;
	while (++i < info->number_of_philo)
		pthread_join(info->philo_tid[i], NULL);
	return (0);
}
