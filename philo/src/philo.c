/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:25:31 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/26 17:56:18 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_fork(t_fork fork);
static void	*stop_philosopher(t_philo philo);
static void	*philo_routine(void *input);

t_philo	*create_philo(t_create_philo create_philo)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->self_ref = &philo;
	philo->rules = create_philo.rules;
	philo->id = create_philo.id;
	philo->is_eating = 0;
	philo->is_thinking = 0;
	philo->is_sleepping = 0;
	philo->print_mutex = create_philo.print_mutex;
	philo->right_fork = create_philo.forks[philo->id - 1];
	if (philo->id == 1)
		philo->left_fork = create_philo.forks[create_philo.forks_amount - 1];
	else
		philo->left_fork = create_philo.forks[philo->id - 2];
	philo->stop = stop_philosopher;
	philo->error = 0;
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

static void	destroy_fork(t_fork fork)
{
	pthread_mutex_destroy(&fork.mutex);
}

static void	*stop_philosopher(t_philo philo)
{
	pthread_join(philo.thread, NULL);
	return (NULL);
}

static void	*philo_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	print_fok_state(philo, LEFT_FORK, millis());
	return (NULL);
}
