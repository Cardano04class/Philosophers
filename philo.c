/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:17:21 by mamir             #+#    #+#             */
/*   Updated: 2024/12/24 23:17:13 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_usleep(size_t time)
{
    
    size_t start;
    start = get_time();
    while ((get_time() - start) < time)
       usleep(500);     
}

void ft_init_global_philos(t_pthread_philosophers *global_philo, char **argv)
{
    global_philo->number_of_philosophers = ft_atoi(argv[1]);
    global_philo->time_to_die = ft_atoi(argv[2]);
    global_philo->time_to_eat = ft_atoi(argv[3]);
    global_philo->time_to_sleep = (size_t)(ft_atoi(argv[4]));
    global_philo->x0 = get_time();
    global_philo->break_routine = 0;
    if (argv[5])
        global_philo->philo_eat_count = ft_atoi(argv[5]);
}

void ft_init_philos(t_philosophers_data *private_data,t_pthread_philosophers *global_philo, pthread_mutex_t *forks, char **argv)
{

    ft_init_global_philos(global_philo, argv);
    int i = 0;
    
    
    while (i < global_philo->number_of_philosophers)
        pthread_mutex_init(&forks[i++], NULL);
    i = 0;
    while (i < global_philo->number_of_philosophers) 
    {
        private_data[i].philo = global_philo;
        private_data[i].philosophers_id = i + 1;
        private_data[i].left_fork = &forks[i];
        private_data[i].right_fork = &forks[(i + 1) % global_philo->number_of_philosophers];
        private_data[i].eat_count = 0;
        i++;  
    }
}


void ft_clean(t_philosophers_data *private_philo, pthread_mutex_t *forks, char **av, pthread_t *threads)
{
    int i = 0;
    free(threads);
    i = 0;
    if (forks)
    {
        while (i < ft_atoi(av[1]))
            pthread_mutex_destroy(&forks[i++]);
        i++;
    }
    free(private_philo->philo);
    free(private_philo);
    free(forks);
}

void ft_print(t_philosophers_data *private_philo, size_t time, char *str)
{
    if (private_philo->philo->break_routine == 1)
        printf("%d %zu %s\n", private_philo->philosophers_id, time, str);
}

void eating(t_philosophers_data *p_data)
{
    size_t start = p_data->philo->x0;
    pthread_mutex_t* first_take = p_data->left_fork;
    pthread_mutex_t* second_take = p_data->right_fork;
    if (p_data->philosophers_id % 2 != 0){
        first_take = p_data->right_fork;
        second_take = p_data->left_fork;
    }
    pthread_mutex_lock(first_take);
    printf("%d %zu has taken a fork\n", p_data->philosophers_id, get_time() - start);
    pthread_mutex_lock(second_take);
    printf("%d %zu has taken a fork\n", p_data->philosophers_id, get_time() - start);
    ft_usleep(p_data->philo->time_to_eat);
    /**/
    p_data->philosopher_last_eat = get_time() - start;    
    p_data->eat_count++;
    /**/
    printf("%d %zu is eating\n", p_data->philosophers_id, get_time() - start);
    pthread_mutex_unlock(first_take);
    pthread_mutex_unlock(second_take);
    
    
}

void sleeping(t_philosophers_data *p_data)
{
    size_t start = p_data->philo->x0;
    printf("%d %zu is sleeping\n", p_data->philosophers_id, get_time() - start);
    ft_usleep(p_data->philo->time_to_sleep);
}

void thinking(t_philosophers_data *p_data)
{
    size_t start = p_data->philo->x0;
    printf("%d %zu is thinking\n", p_data->philosophers_id, get_time() - start);
}

void *routine(t_philosophers_data *p_data)
{
    int i = 0;
    while (1)
    {
        eating(p_data);
        if (p_data->philo->break_routine == 1)
        {
            ft_print(p_data, get_time() - p_data->philo->x0, "died");
            break;
        }
        printf("break_routine = %d\n", p_data->philo->break_routine);
        sleeping(p_data);
        thinking(p_data);
        i++;
    }
    return NULL;   
}

void *ft_monitor(t_philosophers_data *private_philo)
{
    int i = 0;

    while (i < private_philo->philo->number_of_philosophers)
    {
        printf("AAAAAAAAAAA\n");
        if (private_philo->philo->time_to_die - private_philo->philosopher_last_eat < 0)
        {
            printf("ABBBBBBBB\n");
            private_philo->philo->break_routine = 1;
            break;
        }
        i++;
    }
    return NULL;
}
int main(int ac, char **av)
{
    t_pthread_philosophers *global_philo;
    t_philosophers_data *private_philo;
    pthread_mutex_t *forks;
    pthread_t *threads;
    pthread_t monitor;
    if (ac < 5)
        return 1;
    if (ft_parse_args(ac , av))
        return 1;
    int n_philo = ft_atoi(av[1]);
    global_philo = malloc(sizeof(t_pthread_philosophers) * n_philo);
    private_philo = malloc(sizeof(t_philosophers_data) * n_philo);
    forks = malloc(sizeof(pthread_mutex_t) * n_philo);
    threads = malloc(sizeof(pthread_t) * n_philo);

    if (!global_philo || !private_philo || !forks || !threads)
        ft_clean(private_philo, forks, av, threads);
        
    ft_init_philos(private_philo, global_philo, forks, av);
    int i = 0;
    while (i < n_philo)
    {
        pthread_create(&threads[i], NULL, (void *)routine, &private_philo[i]);
        i++;
    }
    // ft_monitor(private_philo);
    pthread_create(&monitor, NULL, (void *)ft_monitor, &private_philo);
    pthread_join(monitor, NULL);
    i = 0;
    while (i < private_philo->philo->number_of_philosophers)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    ft_clean(private_philo, forks,av,threads);
    return 0;
}
