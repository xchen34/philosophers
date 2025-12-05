/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoniechen <leoniechen@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:13:07 by leochen           #+#    #+#             */
/*   Updated: 2024/07/19 23:49:15 by leoniechen       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	all_eaten(t_sim *sim)
{
	int	i;
	int	full;

	full = 0;
	i = 0;
	pthread_mutex_lock(&sim->meal_lock);
	while (i < sim->nb_philo)
	{
		if (sim->philo[i].meals_eaten >= sim->must_eat_meals)
			full++;
		i++;
	}
	pthread_mutex_unlock(&sim->meal_lock);
	if (full == sim->nb_philo)
	{
		pthread_mutex_lock(&sim->stop_sim_lock);
		sim->stop_sim = 1;
		pthread_mutex_unlock(&sim->stop_sim_lock);
		return (1);
	}
	return (0);
}

int	is_dead(t_philo *philo)
{
	long long	current;
	int			dead;

	dead = 0;
	current = get_current_time();
	pthread_mutex_lock(&philo->sim->last_meal_lock);
	if (current - philo->last_meal > philo->sim->time_to_die)
		dead = 1;
	pthread_mutex_unlock(&philo->sim->last_meal_lock);
	if (dead)
	{
		pthread_mutex_lock(&philo->sim->stop_sim_lock);
		if (!philo->sim->stop_sim)
		{
			philo->sim->stop_sim = 1;
			pthread_mutex_unlock(&philo->sim->stop_sim_lock);
			pthread_mutex_lock(&philo->sim->print_lock);
			printf("%lld %d died\n", get_current_time()
				- philo->sim->sim_start, philo->id);
			pthread_mutex_unlock(&philo->sim->print_lock);
		}
		else
			pthread_mutex_unlock(&philo->sim->stop_sim_lock);
	}
	return (dead);
}

static void	stop_simulation(t_sim *sim)
{
	pthread_mutex_lock(&sim->stop_sim_lock);
	sim->stop_sim = 1;
	pthread_mutex_unlock(&sim->stop_sim_lock);
}

void	check_stop(t_sim *sim)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&sim->stop_sim_lock);
		if (sim->stop_sim)
		{
			pthread_mutex_unlock(&sim->stop_sim_lock);
			break ;
		}
		pthread_mutex_unlock(&sim->stop_sim_lock);
		i = 0;
		while (i < sim->nb_philo)
		{
			if (is_dead(&sim->philo[i]) || (sim->must_eat_meals != -1
					&& all_eaten(sim)))
			{
				stop_simulation(sim);
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}
