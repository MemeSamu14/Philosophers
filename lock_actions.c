/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:45:39 by sfiorini          #+#    #+#             */
/*   Updated: 2025/03/09 16:52:13 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_mod(t_data *data)
{
	int		i;
	t_data	*tmp;
	int		diff;

	i = 0;
	diff = data->philo_num;
	tmp = data;
	while (diff > 1)
	{
		tmp = tmp->left_philo;
		diff--;
	}
	while (i < data->philosophers)
	{
		if (pthread_mutex_lock(&tmp->modify) != 0)
			return ;
		tmp = tmp->right_philo;
		i++;
	}
}

void	unlock_mod(t_data *data)
{
	int		i;
	t_data	*tmp;
	int		diff;

	i = 0;
	diff = data->philo_num;
	tmp = data;
	while (diff > 1)
	{
		tmp = tmp->left_philo;
		diff--;
	}
	while (i < data->philosophers)
	{
		pthread_mutex_unlock(&tmp->modify);
		tmp = tmp->right_philo;
		i++;
	}
}

void	im_writing(t_data *data)
{
	int		i;
	t_data	*tmp;
	int		diff;

	i = 0;
	diff = data->philo_num;
	tmp = data;
	while (diff > 1)
	{
		tmp = tmp->left_philo;
		diff--;
	}
	while (i < data->philosophers)
	{
		if (pthread_mutex_lock(&tmp->writing) != 0)
			return ;
		tmp = tmp->right_philo;
		i++;
	}
}

void	finish_writing(t_data *data)
{
	int		i;
	t_data	*tmp;
	int		diff;

	i = 0;
	diff = data->philo_num;
	tmp = data;
	while (diff > 1)
	{
		tmp = tmp->left_philo;
		diff--;
	}
	while (i < data->philosophers)
	{
		pthread_mutex_unlock(&tmp->writing);
		tmp = tmp->right_philo;
		i++;
	}
}

int	lock_forks(t_data *philo)
{
	if (philo->philo_num == 1)
	{
		if (pthread_mutex_lock(&(philo->right_fork)) != 0)
			return (1);
		if (pthread_mutex_lock(&(philo->left_philo->right_fork)) != 0)
			return (1);
	}
	else
	{
		if (pthread_mutex_lock(&(philo->left_philo->right_fork)) != 0)
			return (1);
		if (pthread_mutex_lock(&(philo->right_fork)) != 0)
			return (1);
	}
	return (0);
}
