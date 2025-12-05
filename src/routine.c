/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoniechen <leoniechen@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:50:54 by leochen           #+#    #+#             */
/*   Updated: 2024/07/19 22:17:34 by leoniechen       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_sleep(t_philo *philo, long long time)
{
	long long	start;

	print_msg(philo, "is sleeping");
	start = get_current_time();
	while ((get_current_time() - start) < time && is_dead(philo) == 0)
		usleep(1000);
}

void	think(t_philo *philo)
{
	print_msg(philo, "is thinking");
	if (philo->sim->nb_philo % 2 != 0 && philo->sim->time_to_think != -1)
		usleep(1000 * philo->sim->time_to_eat);
}

static void	take_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, "has taken a fork");
	}
}

static void	put_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	eat(t_philo *philo)
{
	if (philo->sim->nb_philo == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, "has taken a fork");
		ft_usleep(philo, philo->sim->time_to_die);
		print_msg(philo, "died");
		pthread_mutex_lock(&philo->sim->stop_sim_lock);
		philo->sim->stop_sim = 1;
		pthread_mutex_unlock(&philo->sim->stop_sim_lock);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	take_fork(philo);
	pthread_mutex_lock(&(philo->sim->last_meal_lock));
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&(philo->sim->last_meal_lock));
	print_msg(philo, "is eating");
	ft_usleep(philo, philo->sim->time_to_eat);
	pthread_mutex_lock(&(philo->sim->meal_lock));
	philo->meals_eaten++;
	pthread_mutex_unlock(&(philo->sim->meal_lock));
	put_fork(philo);
}
