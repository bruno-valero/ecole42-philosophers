/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:03:14 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/28 18:26:05 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

static t_input	create_input(int input_data[5]);
static int		init_forks(t_state *state);
static int		init_philosophers(t_state *state);
static void		destroy_state(t_state *state);

t_state	create_state(int input_data[5])
{
	t_state			state;

	printf("create_state\n");
	state.someone_died = 0;
	state.monitor = NULL;
	state.error = ERROR_STATE_OK;
	if (!init_state_mutexes(&state))
		return (state);
	state.input = create_input(input_data);
	free(input_data);
	state.start_time = millis() + (state.input.philos);
	if (!init_forks(&state))
		return (state);
	if (!init_philosophers(&state))
		return (state);
	if (!create_monitor(&state))
	{
		destroy_state(&state);
		return (state);
	}
	destroy_state(&state);
	return (state);
}

static t_input	create_input(int input_data[5])
{
	t_input	input;

	input.philos = input_data[0];
	input.time_to_die = input_data[1];
	input.time_to_eat = input_data[2];
	input.time_to_sleep = input_data[3];
	input.times_to_eat = input_data[4];
	return (input);
}

static int	init_philosophers(t_state *state)
{
	int				i;
	t_create_philo	philo;


	state->philos = malloc(state->input.philos * sizeof(t_philo));
	i = -1;
	while (++i < state->input.philos)
	{
		philo = params_philo(i + 1, state);
		state->philos[i] = create_philo(philo);
		if (state->forks[i]->error)
		{
			state->error = ERROR_ON_FORK_CREATION;
			break ;
		}
	}
	if (state->error == ERROR_ON_PHILO_CREATION)
	{
		while (--i >= 0)
			state->philos[i]->stop(state->philos[i]);
		free(state->philos);
		return (0);
	}
	return (1);
}

static int	init_forks(t_state *state)
{
	int	i;

	state->forks = malloc(state->input.philos * sizeof(t_fork));
	i = -1;
	while (++i < state->input.philos)
	{
		state->forks[i] = create_fork(i + 1);
		if (state->forks[i]->error)
		{
			state->error = ERROR_ON_FORK_CREATION;
			break ;
		}
	}
	if (state->error == ERROR_ON_FORK_CREATION)
	{
		while (--i >= 0)
			state->forks[i]->destroy(state->forks[i]);
		free(state->forks);
		return (0);
	}
	return (1);
}

static void	destroy_state(t_state *state)
{
	int	i;

	i = -1;
	while (++i < state->input.philos)
		state->philos[i]->stop(state->philos[i]);
	free(state->philos);
	while (--i >= 0)
		state->forks[i]->destroy(state->forks[i]);
	free(state->forks);
	state->forks = NULL;
	pthread_mutex_destroy(state->print_mutex);
	free(state->print_mutex);
	if (state->monitor)
	{
		pthread_join(*state->monitor, NULL);
		free(state->monitor);
	}
}
