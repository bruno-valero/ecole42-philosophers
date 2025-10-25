/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:25:31 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/25 16:29:52 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_fork(t_fork fork);
static void	*stop_philosopher(t_philo philo);

t_philo	create_philosopher(
			int id, t_fork *forks, int forks_amount, void *(*routine)(void *))
{
	t_philo	philo;

	philo.self_ref = &philo;
	philo.id = id;
	philo.is_eating = 0;
	philo.right_fork = forks[id - 1];
	if (id == 1)
		philo.left_fork = forks[forks_amount - 1];
	else
		philo.left_fork = forks[id - 2];
	philo.error = pthread_create(&philo.thread, NULL, routine, NULL);
	philo.stop = stop_philosopher;
}

t_fork	create_fork(int id)
{
	t_fork	fork;

	fork.self_ref = &fork;
	fork.id = id;
	fork.is_used_by = 0;
	fork.error = pthread_mutex_init(&fork.mutex, NULL);
	fork.destroy = destroy_fork;
	return (fork);
}

static void	destroy_fork(t_fork fork)
{
	pthread_mutex_destroy(&fork.mutex);
}

static void	*stop_philosopher(t_philo philo)
{
	pthread_join(philo.thread, NULL);
	return (NULL);
}
