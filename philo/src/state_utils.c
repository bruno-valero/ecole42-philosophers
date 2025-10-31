/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:55:16 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/31 19:17:17 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

t_create_philo	params_philo(int id, t_state *state)
{
	t_create_philo	create_philo;

	create_philo.id = id;
	create_philo.everyone_ate_mutex = state->everyone_ate_mutex;
	create_philo.start_time = state->start_time;
	create_philo.every_one_ate = &state->every_one_ate;
	create_philo.someone_died = &state->someone_died;
	create_philo.forks = state->forks;
	create_philo.forks_amount = state->input.philos;
	create_philo.print_mutex = state->print_mutex;
	create_philo.dead_mutex = state->dead_mutex;
	create_philo.rules.philos = state->input.philos;
	create_philo.rules.time_to_die = state->input.time_to_die;
	create_philo.rules.time_to_eat = state->input.time_to_eat;
	create_philo.rules.time_to_sleep = state->input.time_to_sleep;
	create_philo.rules.times_to_eat = state->input.times_to_eat;
	return (create_philo);
}

static void	*mfree(void *ptr);

int	init_state_mutexes(t_state *state)
{
	state->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(state->print_mutex, NULL))
		state->error = 1;
	if (state->error)
		return (!!mfree(state->print_mutex));
	state->everyone_ate_mutex = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(state->everyone_ate_mutex, NULL))
		state->error = 1;
	if (state->error)
		return (!!mfree(state->everyone_ate_mutex));
	state->dead_mutex = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(state->dead_mutex, NULL))
		state->error = 1;
	if (state->error)
		return (!!mfree(state->dead_mutex));
	return (1);
}


static void	*mfree(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}
