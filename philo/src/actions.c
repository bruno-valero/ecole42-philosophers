/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:03:40 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/31 17:06:28 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "philo.h"

void	get_fork(t_philo *philo)
{

	pthread_mutex_lock(&philo->right_fork->mutex);
	print_fok_state(philo, RIGHT_FORK, millis());
	if (verify_death(philo))
	{
		pthread_mutex_unlock(&philo->right_fork->mutex);
		return ;
	}
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_fok_state(philo, LEFT_FORK, millis());
	if (verify_death(philo))
	{
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		return ;
	}
}

void	drop_fork(t_philo *philo)
{
	// if (verify_death(philo))
	// 	return ;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	eat(t_philo *philo, t_eat_state eat_state)
{
	long long	curr_millis;
	long long	diff;

	if (verify_death(philo))
		return ;
	if (eat_state == START_TO_EAT)
	{
		get_fork(philo);
		curr_millis = millis();
		pthread_mutex_lock(philo->last_meal_mutex);
		diff = diff_time(curr_millis, philo->last_meal);
		philo->is_eating = 1;
		philo->last_meal = curr_millis;
		pthread_mutex_unlock(philo->last_meal_mutex);
		print_eatting(philo);
	}
	else
	{
		drop_fork(philo);
		if (philo->rules.times_to_eat > 0)
		{
			philo->last_finished_meal = millis();
			philo->is_eating = 0;
			philo->meals_eaten++;
		}
	}
}

void	think(t_philo *philo, t_think_state think_state)
{
	if (verify_death(philo))
		return ;
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
}

void	ft_sleep(t_philo *philo, t_sleep_state sleep_state)
{
	if (verify_death(philo))
		return ;
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
}
