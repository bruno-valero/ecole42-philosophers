/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:41:13 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/27 19:52:48 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "philo.h"

void	print_fok_state(
		t_philo *philo, t_wich_fork wich_fork, unsigned long time)
{
	if (*philo->someone_died)
		return ;
	if (wich_fork == RIGHT_FORK)
	{
		pthread_mutex_lock(philo->print_mutex);
		printf("[%lu] philo[%d] has taken the right fork\n", time, philo->id);
		pthread_mutex_unlock(philo->print_mutex);
	}
	else
	{
		pthread_mutex_lock(philo->print_mutex);
		printf("[%lu] philo[%d] has taken the left fork\n", time, philo->id);
		pthread_mutex_unlock(philo->print_mutex);
	}
}

void	print_eatting(t_philo *philo)
{
	if (*philo->someone_died)
		return ;
	pthread_mutex_lock(philo->print_mutex);
	printf("[%lu] philo[%d] started to eat\n", philo->last_meal, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

void	print_sleeping(t_philo *philo, unsigned long time)
{
	if (*philo->someone_died)
		return ;
	pthread_mutex_lock(philo->print_mutex);
	printf("[%lu] philo[%d] started to sleep\n", time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

void	print_thinking(t_philo *philo, unsigned long time)
{
	if (*philo->someone_died)
		return ;
	pthread_mutex_lock(philo->print_mutex);
	printf("[%lu] philo[%d] started to think\n", time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

void	print_death(t_philo *philo, unsigned long time)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("[%lu] philo[%d] has died\n", time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}
