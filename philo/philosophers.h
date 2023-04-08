/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerhee <jerhee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:05:58 by jerhee            #+#    #+#             */
/*   Updated: 2023/04/08 18:05:59 by jerhee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>

typedef struct s_info
{
	unsigned int	num_philos;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	num_eat;
	unsigned int	full_philo;
	unsigned int	die;
	long long		start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	event;
}	t_info;

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	eat_count;
	long long		last_eat;
	pthread_mutex_t	fork;
	pthread_t		thread;
	struct s_philo	*left;
	struct s_philo	*right;
	struct s_info	*info;
}	t_philo;

int			parse(int argc, char **argv, t_info *info);
int			philosophers(t_info *info, t_philo *philo);
int			take_fork(t_philo *philo);
void		realse_fork(t_philo *philo);
void		check_philo(t_info *info, t_philo *philo);

int			ft_atoi(const char *str);
long long	cur_time(void);
void		print_state(t_philo *philo, char *str);
void		wait_time(long long start, long long delay);
int			ft_print_error(char *str);

#endif