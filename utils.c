/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:26:52 by mamir             #+#    #+#             */
/*   Updated: 2024/12/26 09:52:33 by mamir            ###   ########.fr       */
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

int	print_err(int n)
{
	if (n == 1)
		printf("Invalid Number of Arguments\n");
	if (n == 2)
		printf("invalid Meal Number \n");
	if (n == 3)
		printf("Invalid Philosophers Number\n");
	if (n == 4)
		printf("Bad Arguments [arg should be >= 60]\n");
	if (n == 5)
		printf("Numeric arguments only\n");
	return (0);
}

int	ft_parse_args(int ac, char **av)
{
	int	i;
	int	x;

	i = 1;
	x = ac;
	if (ac < 5 || ac > 6)
		return (print_err(1), 1);
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (print_err(2), 1);
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200)
		return (print_err(3), 1);
	i = 0;
	while (++i < ac)
		if (!is_all_digits(av[i]))
			return (print_err(5), 1);
	i = 2;
	if (ac == 6)
		x = ac - 1;
	while (i < x)
	{
		if (ft_atoi(av[i]) < 60)
			return (print_err(4), 1);
		i++;
	}
	return (0);
}
