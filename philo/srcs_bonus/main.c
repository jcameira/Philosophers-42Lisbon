/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:48:54 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/13 02:59:24 by jcameira         ###   ########.fr       */
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
	return (0);
}
