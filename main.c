/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:09:06 by sfiorini          #+#    #+#             */
/*   Updated: 2025/03/12 17:42:17 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*philos;

	if (ac < 5 || ac > 6)
		return (printf("Error: wrong number of arguments\n"), 1);
	if (input_checks(av) == 1)
		return (printf("Error: input error\n"), 1);
	philos = alloc_data(av);
	if (philos == NULL)
		return (printf("Error: malloc failed\n"), 1);
	if (initialize_data(ac, av, philos) == 1)
		return (free_all(philos), printf("Error: initialize data failed\n"), 1);
	if (philos->philosophers == 1)
	{
		if (pthread_create(&philos[0].philo, \
			NULL, one_philo, (void *)&philos[0]) != 0)
			return (1);
		if (pthread_join(philos[0].philo, NULL) != 0)
			return (1);
	}
	else
		if (program(philos) != 0)
			return (free_all(philos), \
			printf("Error: something goes wrong\n"), 1);
	free_all(philos);
	return (0);
}

int	program(t_data *philos)
{
	int			i;
	pthread_t	dead;

	i = 0;
	while (i < philos->philosophers)
	{
		if (i % 2 == 1)
			usleep(1000);
		if (pthread_create(&philos[i].philo, NULL, \
			philo_life, (void *)&philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&dead, NULL, dead_fun, (void *)&philos[0]) != 0)
		return (1);
	i = 0;
	while (i < philos->philosophers)
	{
		if (pthread_join(philos[i].philo, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join(dead, NULL) != 0)
		return (1);
	return (0);
}
