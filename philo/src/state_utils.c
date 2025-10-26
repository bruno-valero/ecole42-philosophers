/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:55:16 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/26 17:48:24 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

t_create_philo	params_philo(int id, t_state *state)
{
	t_create_philo	create_philo;

	create_philo.id = id;
	create_philo.forks = state->forks;
	create_philo.forks_amount = state->input.philos;
	create_philo.print_mutex = state->print_mutex;
	create_philo.rules.philos = state->input.philos;
	create_philo.rules.time_to_die = state->input.time_to_die;
	create_philo.rules.time_to_eat = state->input.time_to_eat;
	create_philo.rules.time_to_sleep = state->input.time_to_sleep;
	create_philo.rules.times_to_eat = state->input.times_to_eat;
	return (create_philo);
}
