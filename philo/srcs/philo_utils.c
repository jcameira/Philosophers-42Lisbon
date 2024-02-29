/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:58:43 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/29 19:29:05 by jcameira         ###   ########.fr       */
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
			//if (j == 0)
			//{
			//	if (!isnum(argv[i][j]) || !issign(argv[i][j]))
			//		return (0);
			//}
			//else
				if (!isnum(argv[i][j]))
					return (0);
		}
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long int	num;

	i = 0;
	neg = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			neg = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

u_int64_t	gettimems(u_int64_t start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((((end.tv_sec * 1000000) + end.tv_usec) - start) / 1000);
}
