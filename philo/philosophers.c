/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerhee <jerhee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:05:52 by jerhee            #+#    #+#             */
/*   Updated: 2023/04/08 18:05:54 by jerhee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "philosophers.h"

static int	philo_eating(t_philo *philo)
{
	int	ret;

	ret = 0;
	if (take_fork(philo))
		return (1);
	pthread_mutex_lock(&philo->info->event);
	philo->last_eat = cur_time();
	pthread_mutex_unlock(&philo->info->event);
	print_state(philo, "is eating");
	wait_time(philo->last_eat, philo->info->time_eat);
	pthread_mutex_lock(&philo->info->event);
	philo->eat_count++;
	if (philo->info->num_eat && philo->eat_count == philo->info->num_eat)
		philo->info->full_philo++;
	pthread_mutex_unlock(&philo->info->event);
	realse_fork(philo);
	pthread_mutex_lock(&philo->info->event);
	if (philo->info->die
		|| (philo->info->full_philo >= philo->info->num_philos))
		ret = 1;
	pthread_mutex_unlock(&philo->info->event);
	return (ret);
}

static int	philo_sleeping(t_philo *philo)
{
	int	ret;

	ret = 0;
	print_state(philo, "is sleeping");
	wait_time(cur_time(), philo->info->time_sleep);
	pthread_mutex_lock(&philo->info->event);
	if (philo->info->die
		|| (philo->info->full_philo >= philo->info->num_philos))
		ret = 1;
	pthread_mutex_unlock(&philo->info->event);
	return (ret);
}

static int	philo_thinking(t_philo *philo)
{
	int	ret;

	ret = 0;
	print_state(philo, "is thinking");
	usleep(1000);
	pthread_mutex_lock(&philo->info->event);
	if (philo->info->die
		|| (philo->info->full_philo >= philo->info->num_philos))
		ret = 1;
	pthread_mutex_unlock(&philo->info->event);
	return (ret);
}

static void	*philo_thread(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		if (philo_eating(philo))
			return (NULL);
		if (philo_sleeping(philo))
			return (NULL);
		if (philo_thinking(philo))
			return (NULL);
	}
}

int	philosophers(t_info *info, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	info->start_time = cur_time();
	while (i < info->num_philos)
	{
		philo[i].last_eat = cur_time();
		if (pthread_create(&philo[i].thread, NULL, philo_thread, &philo[i]))
			return (1);
		i++;
	}
	check_philo(info, philo);
	i = 0;
	while (i < info->num_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}
