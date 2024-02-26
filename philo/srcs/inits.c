/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 19:15:26 by jcameira          #+#    #+#             */
/*   Updated: 2024/02/26 20:59:58 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

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
}

void	philo_info_init(t_philo *philo, int philo_id)
{
	philo->id = philo_id;
	philo->r_fork = 0;
	philo->l_fork = 0;
	philo->eating = 0;
	philo->thinking = 1;
	philo->sleeping = 0;
	philo->dead = 0;
}

void	*philos_mutex_init(t_info *info)
{
	int	i;

	info->forks = malloc(sizeof(int) * info->number_of_philo);
	if (!info->forks)
		return (NULL);
	i = -1;
	while (++i < info->number_of_philo)
		info->forks[i] = 1;
	info->philos = malloc(sizeof(t_philo) * info->number_of_philo);
	if (!info->philos)
		return (NULL);
	i = -1;
	while (++i < info->number_of_philo)
		philo_info_init(&info->philos[i], i + 1);
	info->fork_mutex = malloc(sizeof(pthread_mutex_t) * info->number_of_philo);
	if (!info->forks)
		return (NULL);
	i = -1;
	while (++i < info->number_of_philo)
		pthread_mutex_init(&info->fork_mutex[i], NULL);
	pthread_mutex_init(&info->write, NULL);
}

void	threads_init(t_info *info)
{
	int	i;

	info->philo_tid = malloc(sizeof(pthread_t) * info->number_of_philo);
	i = -1;
	while (++i < info->number_of_philo)
		pthread_create(&info->philo_tid[i], NULL, funcao, NULL);
	pthread_create(&info->verify_death, NULL, funcao, NULL);
	
}
