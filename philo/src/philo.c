/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:25:31 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/31 19:18:15 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_fork(t_fork *fork, int execute_free);
static void	*stop_philosopher(t_philo *philo, int execute_free);
static void	*philo_routine(void *input);

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
	t_fork	**self_ref;

	self_ref = fork->self_ref;
	if (!execute_free)
		pthread_mutex_destroy(&fork->mutex);
	if (execute_free)
	{
		free(fork);
		*self_ref = NULL;
	}
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

static void	*philo_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (millis() < philo->start_time)
		;
	if (philo->rules.philos == 1)
	{
		print_fok_state(philo, LEFT_FORK, millis());
		usleep(philo->rules.time_to_die * 1000);
		philo->is_dead = 1;
		*philo->someone_died = philo->rules.time_to_die;
		print_death(philo);
		return (NULL);
	}
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
	if (philo->is_eating)
		pthread_mutex_unlock(&philo->right_fork->mutex);
	return (NULL);
}
