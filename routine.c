/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:12:23 by mamir             #+#    #+#             */
/*   Updated: 2024/12/26 12:13:32 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philosophers_data *p_data)
{
	size_t			time;
	pthread_mutex_t	*first_take;
	pthread_mutex_t	*second_take;

	time = p_data->philo->x0;
	first_take = p_data->left_fork;
	second_take = p_data->right_fork;
	if (p_data->philosophers_id % 2 != 0)
	{
		first_take = p_data->right_fork;
		second_take = p_data->left_fork;
	}
	pthread_mutex_lock(first_take);
	ft_print(p_data, time, "has taken a fork");
	pthread_mutex_lock(second_take);
	ft_print(p_data, time, "has taken a fork");
	ft_print(p_data, time, "is eating");
	p_data->last_eat = get_time();
	p_data->eat_count++;
	ft_usleep(p_data->philo->time_to_eat);
	pthread_mutex_unlock(first_take);
	pthread_mutex_unlock(second_take);
}

void	sleeping(t_philosophers_data *p_data)
{
	size_t	time;

	time = p_data->philo->x0;
	ft_print(p_data, time, "is sleeping");
	ft_usleep(p_data->philo->time_to_sleep);
}

void	thinking(t_philosophers_data *p_data)
{
	size_t	time;

	time = p_data->philo->x0;
	ft_print(p_data, time, "is thinking");
	usleep(100);
}

void	*routine(void *arg)
{
	t_philosophers_data	*p_data;

	p_data = (t_philosophers_data *)arg;
	if (ft_one_philo(p_data) == 1)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&p_data->philo->monitor);
		if (p_data->philo->break_routine == 1)
		{
			pthread_mutex_unlock(&p_data->philo->monitor);
			return (NULL);
		}
		pthread_mutex_unlock(&p_data->philo->monitor);
		eating(p_data);
		sleeping(p_data);
		thinking(p_data);
		if (p_data->philo->number_of_philosophers == 3)
			ft_usleep(1);
	}
	return (NULL);
}

void	*ft_monitor(t_philosophers_data *p_data)
{
	int		i;

	i = 0;
	while (p_data->philo->break_routine == 0
		&& p_data->philo->number_of_philosophers != 1)
	{
		i = 0;
		while (i < p_data->philo->number_of_philosophers)
		{
			pthread_mutex_lock(&p_data->philo->monitor);
			if (get_time() - p_data[i].last_eat > p_data->philo->time_to_die)
			{
				p_data->philo->break_routine = 1;
				printf(RED "%zu %d died\n" RESET, get_time()
					- p_data->philo->x0, p_data->philosophers_id);
				return (pthread_mutex_unlock(&p_data->philo->monitor), NULL);
			}
			pthread_mutex_unlock(&p_data->philo->monitor);
			i++;
		}
		if (ft_monitor_container(p_data) == true)
			return (NULL);
	}
	return (NULL);
}
