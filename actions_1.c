/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:39:45 by sfiorini          #+#    #+#             */
/*   Updated: 2025/03/12 17:40:46 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	t_data	*philos;
	int		i;

	i = 0;
	philos = (t_data *)arg;
	while (someone_is_dead(philos) == 0)
	{
		if (philos->must_eat != -1)
		{
			if (everyone_has_eat(philos) == 1)
			{
				philos->end = 1;
				return (NULL);
			}
		}
		philo_core(philos);
		i++;
	}
	return (NULL);
}

void	philo_core(t_data *philos)
{
	lock_forks(philos);
	eat_fun(philos);
	pthread_mutex_unlock(&(philos->right_fork));
	pthread_mutex_unlock(&(philos->left_philo->right_fork));
	sleep_fun(philos);
	think_fun(philos);
	usleep(1000);
}

void	sleep_fun(t_data *philo)
{
	if (someone_is_dead(philo) == 0)
	{
		im_writing(philo);
		printf("%lld: %d is sleeping\n", get_time() - philo->time_start, \
		philo->philo_num);
		finish_writing(philo);
	}
	manual_usleep(philo->time_to_sleep);
}
