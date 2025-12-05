/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leochen <leochen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:02:34 by leochen           #+#    #+#             */
/*   Updated: 2024/07/19 22:29:05 by leochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h> // INT_MAX INT_MIN
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h> // usleep

# define MAX_PHILO 200

struct	s_sim;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_sim	*sim;
}					t_philo;

typedef struct s_sim
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				must_eat_meals;
	int				stop_sim;
	long long		sim_start;
	t_philo			philo[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	stop_sim_lock;
}					t_sim;

void				init_simulation(t_sim *sim, int ac, char **av);
void				init_philo(t_sim *sim);
int					init_mutexes(t_sim *sim);
long long			get_current_time(void);
int					ft_atoi2(char *s);
int					create_threads(t_sim *sim);
void				*routine(void *arg);
long long			timestamp_diff(long long current, long long start);
void				ms_to_timeval(long long ms, struct timeval *tv);
void				philo_sleep(t_philo *philo, long long time);
void				think(t_philo *philo);
void				eat(t_philo *philo);
void				print_msg(t_philo *philo, char *msg);
void				ft_usleep(t_philo *philo, long long time);
int					all_eaten(t_sim *sim);
int					is_dead(t_philo *philo);
int					check_dead(t_sim *sim);
void				check_stop(t_sim *sim);
void				destroy_all(t_sim *sim);

#endif