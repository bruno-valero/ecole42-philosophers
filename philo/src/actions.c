/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:03:40 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/26 16:45:23 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "philo.h"

void	get_fork(t_philo *philo, t_wich_fork wich_fork)
{
	if (wich_fork == RIGHT_FORK)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		if (!philo->right_fork->is_used_by)
		{
			philo->right_fork->is_used_by = philo->id;
			print_fok_state(philo, RIGHT_FORK, millis());
		}
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		if (!philo->left_fork->is_used_by)
		{
			philo->left_fork->is_used_by = philo->id;
			print_fok_state(philo, RIGHT_FORK, millis());
		}
	}
}

void	drop_fork(t_philo *philo, t_wich_fork wich_fork)
{
	if (wich_fork == RIGHT_FORK)
	{
		if (philo->right_fork->is_used_by == philo->id)
			philo->right_fork->is_used_by = 0;
		pthread_mutex_unlock(&philo->right_fork->mutex);
	}
	else
	{
		if (philo->left_fork->is_used_by == philo->id)
			philo->left_fork->is_used_by = 0;
		pthread_mutex_unlock(&philo->left_fork->mutex);
	}
}

void	eat(t_philo *philo, t_eat_state eat_state)
{
	if (!philo->is_eating && eat_state == START_TO_EAT)
	{
		if (philo->right_fork->is_used_by == philo->id
			&& philo->left_fork->is_used_by == philo->id)
		{
			philo->is_eating = 1;
			philo->last_meal = millis();
		}
	}
	else if (philo->is_eating && eat_state == STOP_TO_EAT)
	{
		philo->is_eating = 0;
		drop_fork(philo, LEFT_FORK);
		drop_fork(philo, RIGHT_FORK);
	}
}

void	think(t_philo *philo, t_think_state think_state)
{
	if (think_state == START_TO_THINK)
	{
		if (!philo->is_eating && !philo->is_thinking && !philo->is_sleepping)
			philo->is_thinking = 1;
	}
	else
		philo->is_thinking = 0;
}

void	ft_sleep(t_philo *philo, t_sleep_state sleep_state)
{
	if (sleep_state == START_TO_SLEEP)
	{
		if (!philo->is_eating && !philo->is_thinking && !philo->is_sleepping)
			philo->is_sleepping = 1;
	}
	else
		philo->is_sleepping = 0;
}
