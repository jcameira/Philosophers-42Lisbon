/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:39:02 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/26 16:12:55 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (argument_error());
	if (!args_check(argv))
		return (inv_argument_error());
	info_init(&info, argc, argv);
	philos_mutex_init(&info);
	threads_init(&info);
	return (0);
}