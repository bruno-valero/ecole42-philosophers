/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:03:40 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/28 18:02:03 by brunofer         ###   ########.fr       */
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
		if (!philo->right_fork->is_used_by)
		{
			philo->right_fork->is_used_by = philo->id;
			print_fok_state(philo, RIGHT_FORK, millis());
			return ((void)pthread_mutex_unlock(philo->pause_mutex));
		}
		pthread_mutex_unlock(&philo->right_fork->mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		if (!philo->left_fork->is_used_by)
		{
			philo->left_fork->is_used_by = philo->id;
			print_fok_state(philo, LEFT_FORK, millis());
			return ((void)pthread_mutex_unlock(philo->pause_mutex));
		}
		pthread_mutex_unlock(&philo->right_fork->mutex);
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
	if (verify_death(philo))
		return ;
	if (!philo->is_eating && eat_state == START_TO_EAT)
	{
		get_fork(philo, RIGHT_FORK);
		get_fork(philo, LEFT_FORK);
		if (philo->right_fork->is_used_by == philo->id
			&& philo->left_fork->is_used_by == philo->id)
		{
			philo->is_eating = 1;
			philo->last_meal = millis();
			print_eatting(philo);
		}
	}
	else if (philo->is_eating && eat_state == STOP_TO_EAT)
	{
		drop_fork(philo, RIGHT_FORK);
		drop_fork(philo, LEFT_FORK);
		philo->is_eating = 0;
		if (*philo->rules.times_to_eat > 0)
			*philo->rules.times_to_eat -= 1;
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
