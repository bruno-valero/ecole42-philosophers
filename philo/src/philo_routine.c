/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:11:55 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/03 18:15:47 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*handle_one_philo(t_philo *philo);
static void	drop_forks_on_death(t_philo *philo);

void	*philo_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (millis() < philo->start_time)
		;
	if (philo->rules.philos == 1)
		return (handle_one_philo(philo));
	if (philo->rules.times_to_eat <= 0)
		philo->meals_eaten = -5;
	while (!verify_death(philo)
		&& philo->meals_eaten < philo->rules.times_to_eat)
		philo_routine_step(philo);
	if (philo->meals_eaten == philo->rules.times_to_eat)
	{
		pthread_mutex_lock(philo->everyone_ate_mutex);
		*philo->every_one_ate += 1;
		pthread_mutex_unlock(philo->everyone_ate_mutex);
	}
	drop_forks_on_death(philo);
	return (NULL);
}

static void	*handle_one_philo(t_philo *philo)
{
	print_fok_state(philo, LEFT_FORK, millis());
	usleep(philo->rules.time_to_die * 1000);
	philo->is_dead = 1;
	*philo->someone_died = philo->rules.time_to_die;
	print_death(philo);
	return (NULL);
}

static void	drop_forks_on_death(t_philo *philo)
{
	if (philo->is_eating == 3)
		drop_fork(philo);
	if (philo->is_eating == 1)
		pthread_mutex_unlock(&philo->right_fork->mutex);
	if (philo->is_eating == 2)
		pthread_mutex_unlock(&philo->left_fork->mutex);
}
