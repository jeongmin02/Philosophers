/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerhee <jerhee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:05:40 by jerhee            #+#    #+#             */
/*   Updated: 2023/04/08 18:05:43 by jerhee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	parse_man_opt(char **argv, t_info *info)
{
	info->num_philos = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	info->num_eat = 0;
	info->full_philo = 0;
	info->die = 0;
	if (!info->num_philos || !info->time_die
		|| !info->time_eat || !info->time_sleep)
		return (1);
	return (0);
}

static int	parse_add_opt(char **argv, t_info *info)
{
	info->num_eat = ft_atoi(argv[5]);
	if (!info->num_eat)
		return (1);
	return (0);
}

int	parse(int argc, char **argv, t_info *info)
{
	if (argc == 5)
		return (parse_man_opt(argv, info));
	else if (argc == 6)
	{
		if (parse_man_opt(argv, info))
			return (1);
		return (parse_add_opt(argv, info));
	}
	else
		return (1);
}
