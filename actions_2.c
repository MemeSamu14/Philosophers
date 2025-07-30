/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:39:45 by sfiorini          #+#    #+#             */
/*   Updated: 2025/03/12 17:39:20 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *arg)
{
	t_data	*philo;

	philo = (t_data *)arg;
	printf("%lld: %d is thinking\n", get_time() - philo->time_start, \
	philo->philo_num);
	manual_usleep(philo->time_to_die);
	printf("%lld: %d is dead\n", get_time() - philo->time_start, \
	philo->philo_num);
	return (NULL);
}

void	think_fun(t_data *philo)
{
	if (someone_is_dead(philo) == 0 && philo->thinking == 0)
	{
		im_writing(philo);
		printf("%lld: %d is thinking\n", get_time() - philo->time_start, \
		philo->philo_num);
		finish_writing(philo);
		lock_mod(philo);
		philo->thinking = 1;
		unlock_mod(philo);
	}
}

void	eat_fun(t_data *philo)
{
	long long	time;

	if (someone_is_dead(philo) == 0)
	{
		lock_mod(philo);
		time = get_time() - philo->time_start;
		im_writing(philo);
		printf("%lld: %d has taken fork\n", time, philo->philo_num);
		printf("%lld: %d has taken fork\n", time, philo->philo_num);
		printf("%lld: %d is eating\n", time, philo->philo_num);
		finish_writing(philo);
		philo->last_eat = get_time();
		unlock_mod(philo);
	}
	manual_usleep(philo->time_to_eat);
	eat_modify(philo);
}

void	eat_modify(t_data *philo)
{
	lock_mod(philo);
	philo->thinking = 0;
	philo->eat_times++;
	unlock_mod(philo);
}
