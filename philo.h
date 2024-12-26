/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:16:01 by mamir             #+#    #+#             */
/*   Updated: 2024/12/26 12:16:28 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "limits.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>
# define RED "\x1B[31m"
# define RESET "\033[0m"
# include <stdbool.h>

typedef struct s_pthread_philosophers
{
	int						number_of_philosophers;
	size_t					time_to_die;
	size_t					time_to_sleep;
	int						time_to_eat;
	int						philo_eat_count;
	int						op;
	size_t					x0;
	pthread_mutex_t			*forks;
	pthread_mutex_t			monitor;
	int						break_routine;
	int						end_sim;
}							t_pthread_philosophers;

typedef struct s_philosophers_data
{
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	int						philosophers_id;
	int						eat_count;
	size_t					last_eat;
	t_pthread_philosophers	*philo;
}							t_philosophers_data;
/*-----------------Init-----------------*/
void					init_global_philos(t_pthread_philosophers *global_philo,
							char **argv);
void					ft_init_philos(t_philosophers_data *private_data,
							char **argv);
void					ft_clean(t_philosophers_data *private_philo,
							char **av, pthread_t *threads);

/*-------------------Utils-----------------*/
int						ft_atoi(const char *str);
int						is_all_digits(char *str);
int						ft_parse_args(int ac, char **av);
size_t					get_time(void);
void					ft_usleep(size_t time);
/*----------------------------Routine----------------------*/
void					eating(t_philosophers_data *p_data);
void					sleeping(t_philosophers_data *p_data);
void					thinking(t_philosophers_data *p_data);
void					*routine(void *arg);
void					*ft_monitor(t_philosophers_data *p_data);
void					ft_print(t_philosophers_data *p_data,
							size_t time, char *str);
int						ft_one_philo(t_philosophers_data *p_data);
bool					ft_monitor_container(t_philosophers_data *p_data);

#endif