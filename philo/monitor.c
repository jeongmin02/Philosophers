/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerhee <jerhee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:05:34 by jerhee            #+#    #+#             */
/*   Updated: 2023/04/08 18:05:36 by jerhee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "philosophers.h"

static int	check_all_full(t_info *info)
{
	int	full;

	full = 0;
	pthread_mutex_lock(&info->event);
	if (info->full_philo >= info->num_philos)
		full = 1;
	pthread_mutex_unlock(&info->event);
	return (full);
}

static int	check_time_die(t_info *info, t_philo philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&info->event);
	if ((cur_time() - philo.last_eat) > info->time_die)
		ret = 1;
	pthread_mutex_unlock(&info->event);
	return (ret);
}

void	check_philo(t_info *info, t_philo *philo)
{
	unsigned int	i;

	while (1)
	{
		i = 0;
		while (i < info->num_philos)
		{
			if (check_time_die(info, philo[i]))
			{
				pthread_mutex_lock(&info->event);
				info->die = 1;
				pthread_mutex_unlock(&info->event);
				pthread_mutex_lock(&info->print);
				printf("%lld %d %s\n", cur_time() - info->start_time,
					philo[i].id, "died");
				pthread_mutex_unlock(&info->print);
				return ;
			}
			if (check_all_full(info) == 1)
				return ;
			i++;
		}
		usleep(1000);
	}
}
