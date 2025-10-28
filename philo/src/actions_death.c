/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:29:45 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/28 17:26:50 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "philo.h"

t_philo	*verify_death(t_philo *philo)
{
	unsigned long	curr_milli;
	unsigned long	diff;

	curr_milli = millis();
	if (curr_milli > philo->last_meal)
		diff = curr_milli - philo->last_meal;
	else
		diff = philo->last_meal - curr_milli;
	if (diff >= (unsigned long)philo->rules.time_to_die)
	{
		philo->is_dead = 1;
		pthread_mutex_lock(philo->dead_mutex);
		*philo->someone_died = curr_milli - philo->start_time;
		pthread_mutex_unlock(philo->dead_mutex);
		return (philo);
	}
	return (NULL);
}
