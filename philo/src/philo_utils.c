/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:32:31 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/03 18:31:13 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_create_philo create_philo, t_philo *philo)
{
	philo->self_ref = &philo;
	philo->start_time = create_philo.start_time;
	philo->every_one_ate = create_philo.every_one_ate;
	philo->someone_died = create_philo.someone_died;
	philo->rules = create_philo.rules;
	philo->id = create_philo.id;
	philo->everyone_ate_mutex = create_philo.everyone_ate_mutex;
	philo->meals_eaten_mutex = create_philo.meals_eaten_mutex;
	philo->print_mutex = create_philo.print_mutex;
	philo->dead_mutex = create_philo.dead_mutex;
	philo->right_fork = create_philo.forks[philo->id - 1];
	if (philo->id == 1)
	{
		philo->right_fork = create_philo.forks[create_philo.forks_amount - 1];
		philo->left_fork = create_philo.forks[philo->id - 1];
	}
	else
		philo->left_fork = create_philo.forks[philo->id - 2];
}

static void	philo_sleep(t_philo *philo)
{
	if (verify_death(philo))
		return ;
	ft_sleep(philo, START_TO_SLEEP);
	usleep(1000 * philo->rules.time_to_sleep);
	ft_sleep(philo, STOP_TO_SLEEP);
}

static void	philo_eat(t_philo *philo)
{
	long long	curr_millis;
	long long	diff;

	if (verify_death(philo))
		return ;
	eat(philo, START_TO_EAT);
	curr_millis = millis();
	diff = diff_time(curr_millis, philo->last_meal);
	if (diff + philo->rules.time_to_eat >= philo->rules.time_to_die)
	{
		curr_millis = philo->rules.time_to_die - diff;
		if (curr_millis <= 0)
			curr_millis = 1;
		usleep(1000 * curr_millis);
		eat(philo, STOP_TO_EAT);
		verify_death(philo);
		return ;
	}
	usleep(1000 * philo->rules.time_to_eat);
	eat(philo, STOP_TO_EAT);
}

void	philo_think(t_philo *philo)
{
	if (verify_death(philo))
		return ;
	think(philo, START_TO_THINK);
	usleep(1000);
	think(philo, STOP_TO_THINK);
}

void	philo_routine_step(t_philo *philo)
{
	if (philo->id % 2)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	else
	{
		philo_sleep(philo);
		philo_think(philo);
		philo_eat(philo);
	}
}
