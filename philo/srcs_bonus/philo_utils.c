/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:56:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/13 02:57:02 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	args_check(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		if (ft_atoi(argv[i]) == 0)
			return (0);
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][0] == '+')
			{
				if (!(argv[i][1] >= 48 && argv[i][1] <= 57))
					return (0);
			}
			else
				if (!(argv[i][j] >= 48 && argv[i][j] <= 57))
					return (0);
		}
	}
	return (1);
}
