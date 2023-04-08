/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerhee <jerhee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:05:47 by jerhee            #+#    #+#             */
/*   Updated: 2023/04/08 18:05:48 by jerhee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_fork(t_philo *philo)
{
	if (philo->info->num_philos == 1)
		return (1);
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->left->fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right->fork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right->fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left->fork);
		print_state(philo, "has taken a fork");
	}
	return (0);
}

void	realse_fork(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(&philo->left->fork);
		pthread_mutex_unlock(&philo->right->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->right->fork);
		pthread_mutex_unlock(&philo->left->fork);
	}
}
