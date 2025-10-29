/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:03:40 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/29 20:18:28 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "philo.h"

void	get_fork(t_philo *philo, t_wich_fork wich_fork)
{
	if (verify_death(philo))
		return ;
	pthread_mutex_lock(philo->pause_mutex);
	if (wich_fork == RIGHT_FORK)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_fok_state(philo, RIGHT_FORK, millis());
		pthread_mutex_unlock(&philo->right_fork->mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_fok_state(philo, LEFT_FORK, millis());
		pthread_mutex_unlock(&philo->left_fork->mutex);
	}
	pthread_mutex_unlock(philo->pause_mutex);
}

void	drop_fork(t_philo *philo, t_wich_fork wich_fork)
{
	if (verify_death(philo))
		return ;
	pthread_mutex_lock(philo->pause_mutex);
	if (wich_fork == RIGHT_FORK)
	{
		if (philo->right_fork->is_used_by == philo->id)
		{
			philo->right_fork->is_used_by = 0;
			pthread_mutex_unlock(&philo->right_fork->mutex);
		}
	}
	else
	{
		if (philo->left_fork->is_used_by == philo->id)
		{
			philo->left_fork->is_used_by = 0;
			pthread_mutex_unlock(&philo->left_fork->mutex);
		}
	}
	pthread_mutex_unlock(philo->pause_mutex);
}

void	eat(t_philo *philo, t_eat_state eat_state)
{
	long long	curr_millis;
	long long	diff;

	if (verify_death(philo))
		return ;
	if (!philo->is_eating && eat_state == START_TO_EAT)
	{
		get_fork(philo, RIGHT_FORK);
		get_fork(philo, LEFT_FORK);
		if (verify_death(philo))
			return ;
		curr_millis = millis();
		diff = diff_time(curr_millis, philo->last_meal);
		// if (diff + philo->rules.time_to_eat < philo->rules.time_to_die)
		// {
		philo->is_eating = 1;
		philo->last_meal = curr_millis;
		print_eatting(philo);
		// }
	}
	else if (philo->is_eating && eat_state == STOP_TO_EAT)
	{
		drop_fork(philo, RIGHT_FORK);
		drop_fork(philo, LEFT_FORK);
		philo->is_eating = 0;
		if (philo->rules.times_to_eat > 0)
		{
			philo->last_finished_meal = millis();
			philo->meals_eaten++;
		}
	}
}

void	think(t_philo *philo, t_think_state think_state)
{
	if (verify_death(philo))
		return ;
	pthread_mutex_lock(philo->pause_mutex);
	if (think_state == START_TO_THINK)
	{
		if (!philo->is_eating && !philo->is_thinking && !philo->is_sleepping)
		{
			philo->is_thinking = 1;
			print_thinking(philo, millis());
		}
	}
	else
		philo->is_thinking = 0;
	pthread_mutex_unlock(philo->pause_mutex);
}

void	ft_sleep(t_philo *philo, t_sleep_state sleep_state)
{
	if (verify_death(philo))
		return ;
	pthread_mutex_lock(philo->pause_mutex);
	if (sleep_state == START_TO_SLEEP)
	{
		if (!philo->is_eating && !philo->is_thinking && !philo->is_sleepping)
		{
			philo->is_sleepping = 1;
			print_sleeping(philo, millis());
		}
	}
	else
		philo->is_sleepping = 0;
	pthread_mutex_unlock(philo->pause_mutex);
}
