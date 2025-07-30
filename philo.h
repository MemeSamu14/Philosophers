/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:31:27 by sfiorini          #+#    #+#             */
/*   Updated: 2025/03/12 17:38:41 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>

typedef struct s_data
{
	//presi dagli argomenti
	int					philosophers;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					must_eat;
	//identifica thread
	pthread_t			philo;
	int					philo_num;
	//azioni
	int					dead;
	int					eat_times;
	int					end;
	int					thinking;
	long long			time_start;
	//fork
	pthread_mutex_t		right_fork;
	//vicini
	struct s_data		*left_philo;
	struct s_data		*right_philo;
	//writing
	pthread_mutex_t		writing;
	pthread_mutex_t		modify;
	//timing
	long long			last_eat;
}	t_data;

// actions_1
void		*philo_life(void *arg);
void		philo_core(t_data *philos);
void		sleep_fun(t_data *philo);
// actions_2
void		*one_philo(void *arg);
void		think_fun(t_data *philo);
void		eat_fun(t_data *philo);
void		eat_modify(t_data *philo);
// checks
int			everyone_has_eat(t_data *philos);
int			they_all_eat(t_data *philos);
int			input_checks(char **av);
int			ft_isanum(char c);
// dead_actions
void		*dead_fun(void *arg);
void		dead_core(t_data *philos, int *flag, long long *time_wait);
int			someone_is_dead(t_data *philo);
// lock_actions
void		lock_mod(t_data *data);
void		unlock_mod(t_data *data);
void		im_writing(t_data *data);
void		finish_writing(t_data *data);
int			lock_forks(t_data *philo);
// main
int			program(t_data *philos);
// set_data
t_data		*alloc_data(char **av);
void		free_all(t_data *philos);
int			ft_atoi(char *ptr);
int			initialize_data(int ac, char **av, t_data *data);
int			init_data(int ac, char **av, t_data *data, int i);
// time_actions
long long	get_time(void);
void		manual_usleep(long long time);
#endif