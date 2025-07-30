/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:57:28 by sfiorini          #+#    #+#             */
/*   Updated: 2025/03/12 12:06:08 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dead_fun(void *arg)
{
	t_data		*philos;
	t_data		*tmp;
	long long	time_wait;
	int			flag;

	flag = 0;
	tmp = (t_data *)arg;
	time_wait = get_time();
	while (flag == 0)
	{
		philos = tmp;
		if (they_all_eat(philos) == 1)
			return (NULL);
		dead_core(philos, &flag, &time_wait);
	}
	return (NULL);
}

void	dead_core(t_data *philos, int *flag, long long *time_wait)
{
	int	i;

	lock_mod(philos);
	i = 0;
	while (i < philos->philosophers)
	{
		if ((get_time() - philos->last_eat) >= (philos->time_to_die))
		{
			im_writing(philos);
			printf("%lld: %d is dead\n", get_time() - (*time_wait), \
			philos->philo_num);
			finish_writing(philos);
			philos->dead = 1;
			(*flag) = 1;
			break ;
		}
		i++;
		philos = philos->right_philo;
	}
	unlock_mod(philos);
}

int	someone_is_dead(t_data *philo)
{
	int		i;
	t_data	*tmp;
	int		diff;

	lock_mod(philo);
	i = 0;
	diff = philo->philo_num;
	tmp = philo;
	while (diff > 1)
	{
		tmp = tmp->left_philo;
		diff--;
	}
	while (i < philo->philosophers)
	{
		if (tmp->dead == 1)
		{
			unlock_mod(philo);
			return (1);
		}
		tmp = tmp->right_philo;
		i++;
	}
	unlock_mod(philo);
	return (0);
}
