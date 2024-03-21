/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:56:42 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/21 02:07:21 by jcameira         ###   ########.fr       */
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

void	log_state(int state, t_philo *philo)
{
	const char	*messages[5] = {MSG_FORK, MSG_EATING, MSG_SLEEPING,
		MSG_THINKING, MSG_DEAD};

	sem_wait(philo->info->sem_print);
	printf(messages[state], gettimems() - philo->info->start_time, philo->id);
	sem_post(philo->info->sem_print);
}

void	in_action(suseconds_t time_to_wait)
{
	suseconds_t	start;

	start = gettimems();
	while (1)
	{
		if (gettimems() - start >= time_to_wait)
			return ;
		usleep(100);
	}
}

suseconds_t	gettimems(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
