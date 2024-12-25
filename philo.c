/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:17:21 by mamir             #+#    #+#             */
/*   Updated: 2024/12/25 22:50:39 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		usleep(500);
	}
}

void	ft_print(t_philosophers_data *p_data, size_t time, char *str)
{
	pthread_mutex_lock(&p_data->philo->monitor);
	if (p_data->philo->break_routine == 0)
	{
		printf("%zu %d %s\n", get_time() - time, p_data->philosophers_id, str);
		pthread_mutex_unlock(&p_data->philo->monitor);
		return ;
	}
	pthread_mutex_unlock(&p_data->philo->monitor);
}

int	ft_one_philo(t_philosophers_data *p_data)
{
	size_t	time;

	time = p_data->philo->x0;
	pthread_mutex_lock(&p_data->philo->monitor);
	if (p_data->philo->number_of_philosophers == 1)
	{
		printf("%zu %d has taken a fork\n", get_time() - time,
			p_data->philosophers_id);
		ft_usleep(p_data->philo->time_to_die);
		pthread_mutex_unlock(&p_data->philo->monitor);
		printf(RED "%zu %d is dead\n" RESET, get_time() - time,
			p_data->philosophers_id);
		return (1);
	}
	pthread_mutex_unlock(&p_data->philo->monitor);
	return (0);
}

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
	ft_usleep(p_data->philo->time_to_eat);
	p_data->philosopher_last_eat = get_time();
	p_data->eat_count++;
	ft_print(p_data, time, "is eating");
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
}
bool	ft_monitor_container(t_philosophers_data *p_data)
{
	int	i;

	i = 0;
	while (i < p_data->philo->number_of_philosophers)
	{
		pthread_mutex_lock(&p_data->philo->monitor);
		if ((p_data[i].eat_count < p_data->philo->philo_eat_count))
		{
			pthread_mutex_unlock(&p_data->philo->monitor);
			return (false);
		}
		pthread_mutex_unlock(&p_data->philo->monitor);
		i++;
	}
	p_data->philo->break_routine = 1;
	return (true);
}

void	*ft_monitor(t_philosophers_data *p_data)
{
	int		i;
	size_t	time;

	i = 0;
	time = p_data->philo->x0;
	while (p_data->philo->break_routine == 0
		&& p_data->philo->number_of_philosophers != 1)
	{
		i = 0;
		while (i < p_data->philo->number_of_philosophers)
		{
			pthread_mutex_lock(&p_data->philo->monitor);
			if (get_time()
				- p_data[i].philosopher_last_eat > p_data->philo->time_to_die)
			{
				p_data->philo->break_routine = 1;
				printf(RED "%zu %d is dead\n" RESET, get_time() - time,
					p_data->philosophers_id);
				pthread_mutex_unlock(&p_data->philo->monitor);
				return (NULL);
			}
			pthread_mutex_unlock(&p_data->philo->monitor);
			i++;
		}
		if (ft_monitor_container(p_data) == true)
			return (NULL);
	}
	return (NULL);
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
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philosophers_data	*p_data;
	pthread_t			*threads;
	int					n_philo;
	pthread_t			monitor;
	int					i;

	n_philo = ft_atoi(av[1]);
	if (ft_parse_args(ac, av))
		return (1);
	p_data = malloc(sizeof(t_philosophers_data) * n_philo);
	p_data->philo = malloc(sizeof(t_pthread_philosophers) * n_philo);
	p_data->philo->forks = malloc(sizeof(pthread_mutex_t) * n_philo);
	threads = malloc(sizeof(pthread_t) * n_philo);
	if (!p_data || !threads || !p_data->philo || !p_data->philo->forks)
		return (ft_clean(p_data, av, threads), 1);
	ft_init_philos(p_data, av);
	i = -1;
	while (++i < n_philo)
		pthread_create(&threads[i], NULL, (void *)routine, &p_data[i]);
	pthread_create(&monitor, NULL, (void *)ft_monitor, p_data);
	pthread_join(monitor, NULL);
	ft_clean(p_data, av, threads);
	return (0);
}
