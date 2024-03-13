/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:58:08 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/13 16:00:03 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	processes_init(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->info->number_of_philo)
	{
		philos[i].pid = fork()
		if ()
	}
}

t_philo	*philo_init(t_info *info)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * info->number_of_philo);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < info->number_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].times_eaten = 0;
		philos[i].info = info;
	}
	return (philos);
}

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
	info->sem_forks = sem_open(SEM_FORKS, O_CREAT, S_IRWXU, info->number_of_philo);
	info->sem_print = sem_open(SEM_PRINT, O_CREAT, S_IRWXU, 1);
	info->sem_eat = sem_open(SEM_EAT, O_CREAT, S_IRWXU, 1);
	info->sem_death = sem_open(SEM_DEATH, O_CREAT, S_IRWXU, 1);
}
