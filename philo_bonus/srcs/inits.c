/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:58:08 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/21 02:06:25 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	end_simulation(t_philo *philos)
{
	pthread_create(&philos->info->kill_philos, NULL, kill_func, philos);
	pthread_detach(philos->info->kill_philos);
}

void	processes_init(t_philo *philos)
{
	int	i;

	if (philos->info->times_must_eat > -1)
	{
		pthread_create(&philos->info->verify_satisfied, NULL, meals_func,
			philos);
		pthread_detach(philos->info->verify_satisfied);
	}
	i = -1;
	philos->info->start_time = gettimems();
	while (++i < philos->info->number_of_philo)
	{
		philos[i].last_meal = gettimems();
		philos[i].pid = fork();
		if (philos[i].pid == 0)
		{
			pthread_create(&philos[i].monitor, NULL, monitor_func, &philos[i]);
			pthread_detach(philos[i].monitor);
			philo_func(&philos[i]);
		}
		usleep(100);
	}
	end_simulation(philos);
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
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_EAT);
	sem_unlink(SEM_DEATH);
	info->sem_forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, S_IRWXU,
			info->number_of_philo);
	info->sem_print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, S_IRWXU, 1);
	info->sem_eat = sem_open(SEM_EAT, O_CREAT | O_EXCL, S_IRWXU, 1);
	sem_wait(info->sem_eat);
	info->sem_death = sem_open(SEM_DEATH, O_CREAT | O_EXCL, S_IRWXU, 1);
	sem_wait(info->sem_death);
}
