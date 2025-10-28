/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:25:31 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/28 18:00:47 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_fork(t_fork *fork);
static void	*stop_philosopher(t_philo *philo);
static void	*philo_routine(void *input);

t_philo	*create_philo(t_create_philo create_philo)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	ft_bzero(philo, sizeof(t_philo));
	philo->last_meal = create_philo.start_time;
	philo->pause_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philo->pause_mutex)
	{
		free(philo);
		return (NULL);
	}
	if (pthread_mutex_init(philo->pause_mutex, NULL))
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

static void	destroy_fork(t_fork *fork)
{
	t_fork	**self_ref;

	self_ref = fork->self_ref;
	pthread_mutex_destroy(&fork->mutex);
	free(fork);
	*self_ref = NULL;
}

static void	*stop_philosopher(t_philo *philo)
{
	t_philo	**self_ref;

	self_ref = philo->self_ref;
	pthread_join(philo->thread, NULL);
	pthread_mutex_destroy(philo->pause_mutex);
	free(philo->pause_mutex);
	free(philo);
	*self_ref = NULL;
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
		*philo->someone_died = philo->rules.time_to_die;
		print_death(philo);
		return (NULL);
	}
	while (!*philo->someone_died && *philo->rules.times_to_eat)
		philo_routine_step(philo);
	return (NULL);
}
