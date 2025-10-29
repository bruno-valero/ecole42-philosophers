/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:27:27 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/29 16:48:45 by brunofer         ###   ########.fr       */
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
	if (state->input.philos == 1)
		return (NULL);
	while (millis() < state->start_time)
		;
	while (!state->someone_died && state->input.philos != state->every_one_ate)
	{
		// pthread_mutex_lock(state->print_mutex);
		// printf("philos: %d, eaten: %d\n", state->input.philos,  state->every_one_ate);
		// pthread_mutex_unlock(state->print_mutex);
		usleep(800);
		handle_death(state, &death_warning);
	}
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
	while (++i < state->input.philos)
	{
		philo = state->philos[i];
		pthread_mutex_lock(philo->pause_mutex);
		if (philo->is_dead)
			died_philo = philo->id;
		else if (verify_death(philo))
		{
			if (!died_philo)
				died_philo = philo->id;
		}
		pthread_mutex_unlock(philo->pause_mutex);
	}
	if (died_philo)
	{
		print_death(state->philos[died_philo - 1]);
		*death_warning = 1;
	}
}
