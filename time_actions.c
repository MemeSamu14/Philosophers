/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:47:17 by sfiorini          #+#    #+#             */
/*   Updated: 2025/03/09 16:13:23 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	long long		time_wait;
	struct timeval	time;

	gettimeofday(&time, NULL);
	time_wait = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_wait);
}

void	manual_usleep(long long time)
{
	long long	tmp;

	tmp = get_time();
	while (1)
	{
		if ((get_time() - tmp) >= time)
			break ;
		usleep(1);
	}
}
