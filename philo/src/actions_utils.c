/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:41:13 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/31 15:18:34 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "philo.h"

void	print_fok_state(
		t_philo *philo, t_wich_fork wich_fork, long long time)
{
	(void)wich_fork;
	if (verify_death(philo))
		return ;
	pthread_mutex_lock(philo->print_mutex);
	if (verify_death(philo))
	{
		pthread_mutex_unlock(philo->print_mutex);
		return ;
	}
	printf("%lld %d has taken a fork\n",
		time - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

void	print_eatting(t_philo *philo)
{
	if (verify_death(philo))
		return ;
	pthread_mutex_lock(philo->print_mutex);
	if (verify_death(philo))
	{
		pthread_mutex_unlock(philo->print_mutex);
		return ;
	}
	printf("%lld %d is eating\n",
		philo->last_meal - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

void	print_sleeping(t_philo *philo, long long time)
{
	if (verify_death(philo))
		return ;
	pthread_mutex_lock(philo->print_mutex);
	if (verify_death(philo))
	{
		pthread_mutex_unlock(philo->print_mutex);
		return ;
	}
	printf("%lld %d is sleeping\n",
		time - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

void	print_thinking(t_philo *philo, long long time)
{
	if (verify_death(philo))
		return ;
	pthread_mutex_lock(philo->print_mutex);
	if (verify_death(philo))
	{
		pthread_mutex_unlock(philo->print_mutex);
		return ;
	}
	printf("%lld %d is thinking\n",
		time - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%lld %d has died\n", *philo->someone_died, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}
