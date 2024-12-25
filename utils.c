/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:26:52 by mamir             #+#    #+#             */
/*   Updated: 2024/12/25 17:12:32 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	r;
	int	s;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -s;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		if (r * s > INT_MAX || r * s < INT_MIN)
			exit(1);
		i++;
	}
	return (r * s);
}

int	is_all_digits(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_parse_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (1);
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (1);
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200)
		return (1);
	while (i < ac)
	{
		if (!is_all_digits(av[i]))
		{
			printf("err\n");
			return (1);
		}
		i++;
	}
	return (0);
}
