/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:27:27 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/27 20:00:01 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"
#include "state.h"

static void	*monitor_routine(void *param);
static void	verify_death(t_state *state);

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

	state = (t_state *)param;
	while (millis() < state->start_time)
		;
	while (!state->someone_died)
	{
		usleep(900);
		verify_death(state);
	}
	return (NULL);
}

static void	verify_death(t_state *state)
{
	int				i;
	unsigned long	curr_milli;
	t_philo			*philo;
	int				died_philo;

	died_philo = 0;
	curr_milli = millis();
	i = -1;
	while (++i < state->input.philos)
	{
		philo = state->philos[i];
		pthread_mutex_lock(philo->pause_mutex);
		if (curr_milli - philo->last_meal > (unsigned long)state->input.time_to_die * 100)
		{
			philo->is_dead = 1;
			state->someone_died = 1;
			if (!died_philo)
				died_philo = philo->id;
		}
		pthread_mutex_unlock(philo->pause_mutex);
	}
	if (died_philo)
		print_death(state->philos[died_philo - 1], millis());
}
