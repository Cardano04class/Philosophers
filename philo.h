/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:16:01 by mamir             #+#    #+#             */
/*   Updated: 2024/12/25 22:19:51 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
#include <time.h>
#include "limits.h"
#include <sys/time.h>
#define RED  "\x1B[31m"
#define RESET   "\033[0m"
#include <stdbool.h>
typedef struct s_pthread_philosophers
{
    int                        number_of_philosophers;
    size_t                        time_to_die;
    size_t                        time_to_sleep;
    int                        time_to_eat;
    int                        philo_eat_count;
    size_t                     x0;
    pthread_mutex_t            *forks;
    pthread_mutex_t            monitor;
    pthread_mutex_t            death;
    int                        break_routine;
    int                        end_sim;
}                            t_pthread_philosophers;

typedef struct s_philosophers_data
{
    pthread_mutex_t            *left_fork;
    pthread_mutex_t            *right_fork;
    int                        philosophers_id;
    int                        eat_count;
    size_t                    philosopher_last_eat;
    t_pthread_philosophers    *philo;
}                            t_philosophers_data;
/*-----------------Init-----------------*/
void                        ft_init_global_philos(t_pthread_philosophers *global_philo, char **argv);
void                        ft_init_philos(t_philosophers_data *private_data, char **argv);
void                        ft_clean(t_philosophers_data *private_philo,char **av, pthread_t *threads);

/*-------------------Utils-----------------*/
int                         ft_atoi(const char *str);
int                         is_all_digits(char *str);
int                         ft_parse_args(int ac, char **av);
size_t                      get_time();

#endif