/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:27:27 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/28 18:33:25 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"
#include "state.h"

static void	*monitor_routine(void *param);
static void	handle_death(t_state *state, int *death_warning);

int	create_monitor(t_state *state)
{
	state->monitor = malloc(sizeof(pthread_t));
	if (!state->monitor)
	{
		state->error = ERROR_ON_MONITOR_CREATION;
		state->monitor = NULL;
		return (0);
	}
	if (pthread_create(state->monitor, NULL, monitor_routine, state))
	{
		state->error = ERROR_ON_MONITOR_CREATION;
		return (0);
	}
	return (1);
}

static void	*monitor_routine(void *param)
{
	t_state	*state;
	int		death_warning;

	death_warning = 0;
	state = (t_state *)param;
	while (millis() < state->start_time)
		;
	pthread_mutex_lock(state->print_mutex);
	printf("monitor.routine before: %p\n", state->philos);
	pthread_mutex_unlock(state->print_mutex);
	while (!state->someone_died)
	{
		usleep(800);
		handle_death(state, &death_warning);
	}
	pthread_mutex_lock(state->print_mutex);
	printf("monitor.routine after: %p\n", state->philos);
	printf("monitor.death_warning: %d\n", death_warning);
	pthread_mutex_unlock(state->print_mutex);
	if (!death_warning)
		handle_death(state, &death_warning);
	return (NULL);
}

static void	handle_death(t_state *state, int *death_warning)
{
	int				i;
	unsigned long	curr_milli;
	t_philo			*philo;
	int				died_philo;

	died_philo = 0;
	curr_milli = millis();
	i = -1;
	pthread_mutex_lock(state->print_mutex);
	printf("monitor.death_warning: %d\n", *death_warning);
	printf("monitor.handle_death after: %p\n", state->philos);
	pthread_mutex_unlock(state->print_mutex);
	while (++i < state->input.philos)
	{
		philo = state->philos[i];
		pthread_mutex_lock(state->print_mutex);
		printf("monitor.death_warning: %d\n", *death_warning);
		printf("philo start: %p\n", philo);
		pthread_mutex_unlock(state->print_mutex);

		pthread_mutex_lock(philo->pause_mutex);

		pthread_mutex_lock(state->print_mutex);
		printf("monitor.death_warning: %d\n", *death_warning);
		printf("philo end: %p\n", philo);
		pthread_mutex_unlock(state->print_mutex);
		if (philo->is_dead)
			died_philo = philo->id;
		else if (verify_death(philo))
		{
			if (!died_philo)
				died_philo = philo->id;
		}
		pthread_mutex_unlock(philo->pause_mutex);
		pthread_mutex_lock(state->print_mutex);
		printf("monitor.death_warning: %d\n", *death_warning);
		printf("philo end: %p\n", philo);
		pthread_mutex_unlock(state->print_mutex);
	}
	pthread_mutex_lock(state->print_mutex);
	printf("monitor.handle_death before: %p\n", state->philos);
	pthread_mutex_unlock(state->print_mutex);
	if (died_philo)
	{
		print_death(state->philos[died_philo - 1]);
		*death_warning = 1;
	}
}
