/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:05:43 by leochen           #+#    #+#             */
/*   Updated: 2024/07/19 22:28:08 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	pthread_mutex_lock(&philo->sim->stop_sim_lock);
	if (philo->sim->stop_sim == 0)
		printf("%lld %d %s\n", get_current_time() - philo->sim->sim_start,
			philo->id, msg);
	pthread_mutex_unlock(&philo->sim->stop_sim_lock);
	pthread_mutex_unlock(&philo->sim->print_lock);
}

void	ft_usleep(t_philo *philo, long long time)
{
	long long	start_loop;

	start_loop = get_current_time();
	while (get_current_time() - start_loop < time)
	{
		if (is_dead(philo))
			return ;
		usleep(1000);
	}
}

void	destroy_all(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nb_philo)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->meal_lock);
	pthread_mutex_destroy(&sim->last_meal_lock);
	pthread_mutex_destroy(&sim->stop_sim_lock);
}
