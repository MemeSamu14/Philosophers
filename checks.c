/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:28:14 by sfiorini          #+#    #+#             */
/*   Updated: 2025/03/12 16:07:51 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	everyone_has_eat(t_data *philos)
{
	int		i;
	t_data	*tmp;
	int		diff;
	int		flag;

	lock_mod(philos);
	i = -1;
	flag = 0;
	diff = philos->philo_num + 1;
	tmp = philos;
	while (--diff > 1)
		tmp = tmp->left_philo;
	while (++i < philos->philosophers)
	{
		if (tmp->eat_times >= tmp->must_eat)
			flag++;
		tmp = tmp->right_philo;
	}
	if (flag == tmp->philosophers)
	{
		unlock_mod(philos);
		return (1);
	}
	unlock_mod(philos);
	return (0);
}

int	they_all_eat(t_data *philos)
{
	int		i;
	t_data	*tmp;
	int		diff;

	lock_mod(philos);
	i = 0;
	diff = philos->philo_num;
	tmp = philos;
	while (diff > 1)
	{
		tmp = tmp->left_philo;
		diff--;
	}
	while (i < philos->philosophers)
	{
		if (tmp->end == 1)
		{
			unlock_mod(philos);
			return (1);
		}
		tmp = tmp->right_philo;
		i++;
	}
	unlock_mod(philos);
	return (0);
}

int	input_checks(char **av)
{
	int	i;
	int	j;

	i = 1;
	if (av[1][0] == '0')
		return (1);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isanum(av[i][j]) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_isanum(char c)
{
	if ((c >= '0' && c <= '9' ) || (c == '+'))
		return (0);
	return (1);
}
/* 
int	high_priority(t_data *philos)
{
	int		i;
	t_data	*tmp;
	int		diff;
	int		flag;

	i = 0;
	flag = 0;
	diff = philos->philo_num;
	tmp = philos;
	while (diff > 1)
	{
		tmp = tmp->left_philo;
		diff--;
	}
	while (i < philos->philosophers)
	{
		if (flag <= tmp->priority)
			flag = tmp->priority;
		tmp = tmp->right_philo;
		i++;
	}
	if (flag == philos->priority)
		return (1);
	return (0);
} */
