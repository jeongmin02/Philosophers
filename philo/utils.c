/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerhee <jerhee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:06:03 by jerhee            #+#    #+#             */
/*   Updated: 2023/04/08 18:06:06 by jerhee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "philosophers.h"

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					sign;

	sign = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str >= 48 && *str <= 57)
	{
		result = result * 10 + *str - 48;
		str++;
	}
	if (*str != '\0' || sign == -1)
		return (0);
	return (result * sign);
}

long long	cur_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void	print_state(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->print);
	pthread_mutex_lock(&philo->info->event);
	if (!philo->info->die
		&& !(philo->info->full_philo == philo->info->num_philos))
		printf("%lld %d %s\n", cur_time() - philo->info->start_time,
			philo->id, str);
	pthread_mutex_unlock(&philo->info->event);
	pthread_mutex_unlock(&philo->info->print);
}

void	wait_time(long long start, long long delay)
{
	while (cur_time() - start < delay)
		usleep(100);
}

int	ft_print_error(char *str)
{
	printf("%s\n", str);
	return (1);
}
