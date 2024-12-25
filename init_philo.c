/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 12:02:34 by mamir             #+#    #+#             */
/*   Updated: 2024/12/25 22:46:55 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_init_global_philos(t_pthread_philosophers *global_philo, char **argv)
{
	global_philo->number_of_philosophers = ft_atoi(argv[1]);
	global_philo->time_to_die = ft_atoi(argv[2]);
	global_philo->time_to_eat = ft_atoi(argv[3]);
	global_philo->time_to_sleep = (size_t)(ft_atoi(argv[4]));
	global_philo->x0 = get_time();
	global_philo->break_routine = 0;
	pthread_mutex_init(&global_philo->monitor, NULL);
	pthread_mutex_init(&global_philo->death, NULL);
	if (argv[5])
		global_philo->philo_eat_count = ft_atoi(argv[5]);
}

void	ft_init_philos(t_philosophers_data *p_data, char **argv)
{
	int	i;

	ft_init_global_philos(p_data->philo, argv);
	i = 0;
	while (i < p_data->philo->number_of_philosophers)
	{
		pthread_mutex_init(&p_data->philo->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < p_data->philo->number_of_philosophers)
	{
		p_data[i].philo = p_data->philo;
		p_data[i].philosophers_id = i + 1;
		p_data[i].left_fork = &p_data->philo->forks[i];
		p_data[i].right_fork = &p_data->philo->forks[(i + 1)
			% p_data->philo->number_of_philosophers];
		p_data[i].eat_count = 0;
		p_data[i].philosopher_last_eat = p_data->philo->x0;
		i++;
	}
}

void	ft_clean(t_philosophers_data *p_data, char **av, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	i = 0;
	if (p_data)
	{
		if (p_data->philo)
		{
			while (i < p_data->philo->number_of_philosophers)
				pthread_mutex_destroy(&p_data->philo->forks[i++]);
			free(p_data->philo->forks);
			free(p_data->philo);
		}
		free(p_data);
	}
	free(threads);
}
