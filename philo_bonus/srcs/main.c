/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:48:54 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/13 15:56:38 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	main(int argc, char **argv)
{
	t_info	*info;
	t_philo	*philos;
	int		i;

	if (argc < 5 || argc > 6)
		return (argument_number_error());
	if (!args_check(argv))
		return (inv_argument_error());
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
	info_init(info, argc, argv);
	philos = philo_init(info);
	processes_init(philos);
	return (0);
}
