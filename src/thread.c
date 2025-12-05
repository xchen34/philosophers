/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoniechen <leoniechen@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:26:42 by leochen           #+#    #+#             */
/*   Updated: 2024/07/19 22:17:35 by leoniechen       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	create_threads(t_sim *sim)
{
	int	i;

	i = 0;
	sim->sim_start = get_current_time();
	while (i < sim->nb_philo)
	{
		if (pthread_create(&(sim->philo[i].thread), NULL, routine,
				&sim->philo[i]))
			return (1);
		i++;
	}
	check_stop(sim);
	i = 0;
	while (i < sim->nb_philo)
	{
		if (pthread_join(sim->philo[i].thread, NULL))
			return (1);
		i++;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	if (philo->id % 2 == 0)
		usleep(500 * philo->sim->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(&sim->stop_sim_lock);
		if (sim->stop_sim)
		{
			pthread_mutex_unlock(&sim->stop_sim_lock);
			break ;
		}
		pthread_mutex_unlock(&sim->stop_sim_lock);
		eat(philo);
		if (sim->nb_philo == 1 || is_dead(philo) || (sim->must_eat_meals != -1
				&& all_eaten(sim)))
			break ;
		philo_sleep(philo, sim->time_to_sleep);
		think(philo);
	}
	is_dead(philo);
	return (NULL);
}
