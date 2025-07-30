/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:15:30 by sfiorini          #+#    #+#             */
/*   Updated: 2025/03/12 17:37:53 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*alloc_data(char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data) * ft_atoi(av[1]));
	if (data == NULL)
		return (NULL);
	return (data);
}

void	free_all(t_data *philos)
{
	int	i;

	i = 0;
	while (i < philos->philosophers)
	{
		pthread_mutex_destroy(&philos[i].right_fork);
		pthread_mutex_destroy(&philos[i].writing);
		i++;
	}
	free(philos);
}

int	ft_atoi(char *ptr)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || \
	*ptr == '\v' || *ptr == '\f' || *ptr == '\r')
		ptr++;
	if (*ptr == '+' || *ptr == '-')
	{
		if (*ptr == '-')
			sign = -1;
		ptr++;
	}
	while (*ptr >= 48 && *ptr <= 57)
	{
		res = res * 10 + (*ptr - '0');
		ptr++;
	}
	return (res * sign);
}

int	initialize_data(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (init_data(ac, av, &data[i], i) == 1)
			return (1);
		i++;
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		data[i].right_philo = &data[i + 1];
		if (i != 0)
		{
			data[i].left_philo = &data[i - 1];
		}
		i++;
	}
	data[0].left_philo = &data[ft_atoi(av[1]) - 1];
	data[ft_atoi(av[1]) - 1].right_philo = &data[0];
	return (0);
}

//initialize data, if something goes wrong it returns 1 
//in the other hand it return 0
int	init_data(int ac, char **av, t_data *data, int i)
{
	struct timeval	actual_time;

	data->philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	data->philo_num = i + 1;
	data->dead = 0;
	data->end = 0;
	data->eat_times = 0;
	data->thinking = 0;
	gettimeofday(&actual_time, NULL);
	data->time_start = (actual_time.tv_sec * 1000) + \
	(actual_time.tv_usec / 1000);
	data->last_eat = get_time();
	pthread_mutex_init(&data->modify, NULL);
	pthread_mutex_init(&data->writing, NULL);
	pthread_mutex_init(&data->right_fork, NULL);
	return (0);
}
