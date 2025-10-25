/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:03:14 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/25 15:23:49 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

static t_input	create_input(int input_data[5]);

t_state	create_state(int input_data[5])
{
	t_state	state;

	state.input = create_input(input_data);
	free(input_data);
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
