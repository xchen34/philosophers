/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:50:06 by leochen           #+#    #+#             */
/*   Updated: 2024/07/19 22:27:46 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_simulation(t_sim *sim, int ac, char **av)
{
	long long	current_time;

	current_time = get_current_time();
	sim->nb_philo = ft_atoi2(av[1]);
	sim->time_to_die = ft_atoi2(av[2]);
	sim->time_to_eat = ft_atoi2(av[3]);
	sim->time_to_sleep = ft_atoi2(av[4]);
	if (sim->time_to_eat >= sim->time_to_sleep)
		sim->time_to_think = sim->time_to_eat;
	else
		sim->time_to_think = -1;
	if (ac == 6)
		sim->must_eat_meals = ft_atoi2(av[5]);
	else
		sim->must_eat_meals = -1;
	sim->stop_sim = 0;
	sim->sim_start = current_time;
	init_mutexes(sim);
	init_philo(sim);
}

void	init_philo(t_sim *sim)
{
	int			i;
	long long	current_time;

	i = 0;
	current_time = get_current_time();
	while (i < sim->nb_philo)
	{
		sim->philo[i].id = i + 1;
		sim->philo[i].meals_eaten = 0;
		sim->philo[i].last_meal = current_time;
		sim->philo[i].left_fork = &sim->forks[i];
		sim->philo[i].right_fork = &sim->forks[(i + 1) % sim->nb_philo];
		sim->philo[i].sim = sim;
		i++;
	}
}

int	init_mutexes(t_sim *sim)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&sim->print_lock, NULL)
		|| pthread_mutex_init(&sim->meal_lock, NULL)
		|| pthread_mutex_init(&sim->last_meal_lock, NULL)
		|| pthread_mutex_init(&sim->stop_sim_lock, NULL))
		return (1);
	while (i < sim->nb_philo)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		printf("gettimeofday failed\n");
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}
