/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:58:43 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/24 19:12:01 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	isnum(char str)
{
	return (str >= 48 && str <= 57);
}

int	issign(char str)
{
	return (str == 43 || str == 45);
}

int	args_check(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (j == 0)
				if (!isnum(argv[i][j]) || !issign(argv[i][j]))
					return (0);
			else
				if (!isnum(argv[i][j]))
					return (0);
		}
	}
	return (1);
}