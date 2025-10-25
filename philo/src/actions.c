/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:03:40 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/25 16:37:15 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	get_fork(t_philo philo, t_wich_fork wich_fork)
{
	if (wich_fork == RIGHT_FORK)
	{
		pthread_mutex_lock(&philo.right_fork.mutex);
		if (!philo.right_fork.is_used_by)
			philo.right_fork.is_used_by = philo.id;
		pthread_mutex_unlock(&philo.right_fork.mutex);
	}
	else
	{
		pthread_mutex_lock(&philo.left_fork.mutex);
		if (!philo.left_fork.is_used_by)
			philo.left_fork.is_used_by = philo.id;
		pthread_mutex_unlock(&philo.left_fork.mutex);
	}
}

void	drop_fork(t_philo philo, t_wich_fork wich_fork)
{
	if (wich_fork == RIGHT_FORK)
	{
		pthread_mutex_lock(&philo.right_fork.mutex);
		if (philo.right_fork.is_used_by == philo.id)
			philo.right_fork.is_used_by = 0;
		pthread_mutex_unlock(&philo.right_fork.mutex);
	}
	else
	{
		pthread_mutex_lock(&philo.left_fork.mutex);
		if (philo.left_fork.is_used_by == philo.id)
			philo.left_fork.is_used_by = 0;
		pthread_mutex_unlock(&philo.left_fork.mutex);
	}
}

void	eat(t_philo philo, t_eat_state eat_state)
{
	if (!philo.is_eating && eat_state == START_TO_EAT)
	{
		pthread_mutex_lock(&philo.right_fork.mutex);
		pthread_mutex_lock(&philo.left_fork.mutex);
		if (philo.right_fork.is_used_by == philo.id
			&& philo.left_fork.is_used_by == philo.id)
			philo.is_eating = 1;
			pthread_mutex_unlock(&philo.right_fork.mutex);
		pthread_mutex_unlock(&philo.left_fork.mutex);
	}
	else if (philo.is_eating && eat_state == STOP_TO_EAT)
	{
		philo.is_eating = 0;
	}
}
