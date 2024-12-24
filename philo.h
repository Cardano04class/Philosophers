/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:16:01 by mamir             #+#    #+#             */
/*   Updated: 2024/12/24 22:49:26 by mamir            ###   ########.fr       */
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
typedef struct s_pthread_philosophers
{
    int                        number_of_philosophers;
    int                        time_to_die;
    size_t                        time_to_sleep;
    int                        time_to_eat;
    int                        philo_eat_count;
    size_t                     x0;
    pthread_mutex_t            *forks;
    // pthread_mutex_t            monitor;
    int                        break_routine;
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

int                         ft_atoi(const char *str);
int                         is_all_digits(char *str);
int                         ft_parse_args(int ac, char **av);

#endif