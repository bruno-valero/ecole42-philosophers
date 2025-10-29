/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:24:38 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/29 20:17:23 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "actions.h"
# include "utils.h"

typedef struct s_fork			t_fork;
struct s_fork
{
	t_fork			**self_ref;
	int				id;
	pthread_mutex_t	mutex;
	int				is_used_by;
	int				error;
	void			(*destroy)(t_fork *fork, int execute_free);
};

typedef struct s_philo_rules	t_philo_rules;
struct s_philo_rules
{
	int	philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_to_eat;
};

typedef struct s_philo			t_philo;
struct s_philo
{
	t_philo			**self_ref;
	int				id;
	long long		start_time;
	pthread_t		thread;
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_philo_rules	rules;
	int				is_eating;
	long long		last_meal;
	long long		last_finished_meal;
	int				is_thinking;
	int				is_sleepping;
	int				is_dead;
	int				meals_eaten;
	int				*every_one_ate;
	long long		*someone_died;
	pthread_mutex_t	*pause_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*dead_mutex;
	int				error;
	void			*(*stop)(t_philo *philo, int execute_free);
};

typedef struct s_create_philo	t_create_philo;
struct s_create_philo
{
	int				id;
	long long		start_time;
	int				*every_one_ate;
	long long		*someone_died;
	t_fork			**forks;
	int				forks_amount;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*pause;
	t_philo_rules	rules;
};

void	init_philo(t_create_philo create_philo, t_philo *philo);
t_philo	*create_philo(t_create_philo create_philo);
t_fork	*create_fork(int id);
void	philo_routine_step(t_philo *philo);

#endif
