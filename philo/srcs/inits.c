/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 19:15:26 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/29 22:27:23 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	info_init(t_info *info, int argc, char **argv)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	info->start_time = (start.tv_sec * 1000000) + start.tv_usec;
	info->number_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->times_must_eat = ft_atoi(argv[5]);
	else
		info->times_must_eat = -1;
	info->finish_sim = 0;
	pthread_mutex_init(&info->write, NULL);
	pthread_mutex_init(&info->time, NULL);
}

void	philo_info_init(t_info *info, t_philo *philo,
			pthread_mutex_t *fork_mutex, int philo_id)
{
	struct timeval	start;
	
	philo->id = philo_id;
	if (info->number_of_philo == 1)
		philo->l_fork = NULL;
	else if (philo_id == 1)
		philo->l_fork = &fork_mutex[info->number_of_philo - 1];
	else
		philo->l_fork = &fork_mutex[philo_id - 2];
	philo->r_fork = &fork_mutex[philo_id - 1];
	philo->eating = 0;
	philo->thinking = 1;
	philo->sleeping = 0;
	philo->dead = 0;
	gettimeofday(&start, NULL);
	philo->current_time = (start.tv_sec * 1000000) + start.tv_usec;
	philo->info = info;
}

pthread_mutex_t	*fork_init(t_info *info)
{
	pthread_mutex_t	*fork_mutex;
	int				i;

	fork_mutex = malloc(sizeof(pthread_mutex_t) * info->number_of_philo);
	if (!fork_mutex)
		return (NULL);
	i = -1;
	while (++i < info->number_of_philo)
		pthread_mutex_init(&fork_mutex[i], NULL);
	return (fork_mutex);
}

t_philo	*philos_init(t_info *info, pthread_mutex_t *fork_mutex)
{
	t_philo *philos;
	int	i;

	philos = malloc(sizeof(t_philo) * info->number_of_philo);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < info->number_of_philo)
		philo_info_init(info, &philos[i], fork_mutex, i + 1);
	return (philos);
}

void	*threads_init(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos[0].info->number_of_philo)
	{
		pthread_create(&philos[i].tid, NULL, &philo_func, &philos[i]);
		usleep(1000);
	}
	pthread_create(&philos[0].info->verify_death, NULL, &death_check, philos);
	return (philos);
}
