/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:25:31 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/03 18:16:35 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_fork(t_fork *fork, int execute_free);
static void	*stop_philosopher(t_philo *philo, int execute_free);

t_philo	*create_philo(t_create_philo create_philo)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	ft_bzero(philo, sizeof(t_philo));
	philo->last_meal = create_philo.start_time;
	philo->last_finished_meal = create_philo.start_time;
	philo->last_meal_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philo->last_meal_mutex)
	{
		free(philo);
		return (NULL);
	}
	if (pthread_mutex_init(philo->last_meal_mutex, NULL))
	{
		philo->error = 1;
		return (philo);
	}
	init_philo(create_philo, philo);
	philo->stop = stop_philosopher;
	philo->error = pthread_create(
			&philo->thread, NULL, philo_routine, philo);
	return (philo);
}

t_fork	*create_fork(int id)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	fork->self_ref = &fork;
	fork->id = id;
	fork->is_used_by = 0;
	fork->error = pthread_mutex_init(&fork->mutex, NULL);
	fork->destroy = destroy_fork;
	return (fork);
}

static void	destroy_fork(t_fork *fork, int execute_free)
{
	if (!execute_free)
		pthread_mutex_destroy(&fork->mutex);
	if (execute_free)
		free(fork);
}

static void	*stop_philosopher(t_philo *philo, int execute_free)
{
	if (!execute_free)
		pthread_join(philo->thread, NULL);
	if (execute_free)
	{
		pthread_mutex_destroy(philo->last_meal_mutex);
		free(philo->last_meal_mutex);
		free(philo);
	}
	return (NULL);
}
