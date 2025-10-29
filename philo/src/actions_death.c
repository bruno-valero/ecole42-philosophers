/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:29:45 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/29 20:38:08 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "philo.h"

t_philo	*verify_death(t_philo *philo)
{
	long long	curr_milli;
	long long	diff;

	if (philo->rules.times_to_eat > 0
		&& philo->meals_eaten == philo->rules.times_to_eat)
		return (NULL);
	pthread_mutex_lock(philo->dead_mutex);
	if (*philo->someone_died)
	{
		pthread_mutex_unlock(philo->dead_mutex);
		return (philo);
	}
	pthread_mutex_unlock(philo->dead_mutex);
	curr_milli = millis();
	diff = diff_time(curr_milli - philo->start_time, philo->last_finished_meal);
	if (diff >= philo->rules.time_to_die)
	{
		philo->is_dead = 1;
		pthread_mutex_lock(philo->dead_mutex);
		*philo->someone_died = curr_milli - philo->start_time;
		pthread_mutex_unlock(philo->dead_mutex);
		return (philo);
	}
	return (NULL);
}

long long	diff_time(long long t1, long long t2)
{
	long long	diff;

	diff = t1 - t2;
	if (diff < 0)
		return (-diff);
	return (diff);
}
