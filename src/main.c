/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:46:57 by leochen           #+#    #+#             */
/*   Updated: 2024/07/19 22:28:30 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	has_arg_err(char **av, int ac);
static int	is_number(char *s);

int	main(int ac, char **av)
{
	t_sim	sim;

	if (ac < 5 || ac > 6 || has_arg_err(av, ac))
	{
		printf("Error:Invalid arguments\n");
		return (1);
	}
	init_simulation(&sim, ac, av);
	if (create_threads(&sim))
		return (destroy_all(&sim), 1);
	check_stop(&sim);
	return (0);
}

static int	has_arg_err(char **av, int ac)
{
	int	i;

	if (ft_atoi2(av[1]) > MAX_PHILO || ft_atoi2(av[1]) <= 0)
		return (1);
	if (ac == 6 && ft_atoi2(av[5]) <= 0)
		return (1);
	i = 2;
	while (i < ac)
	{
		if ((i != 5 && ft_atoi2(av[i]) <= 0) || !is_number(av[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	is_number(char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

int	ft_atoi2(char *s)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*s == ' ' || (*s >= '\t' && *s <= '\r' && *s != '\n' && *s != '\v'
			&& *s != '\f'))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		result = result * 10 + (*s - '0');
		if (result * sign > INT_MAX || result * sign < INT_MIN)
			return (-1);
		s++;
	}
	if (*s == '\0')
		return ((int)(result * sign));
	return (-1);
}
