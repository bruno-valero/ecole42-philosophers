/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:44:01 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/25 19:35:17 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# include <stdlib.h>
# include "philo.h"

typedef struct s_input		t_input;
struct s_input
{
	int	philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_to_eat;
};

typedef enum e_error_state	t_error_state;
enum e_error_state
{
	ERROR_STATE_OK,
	ERROR_ON_FORK_CREATION,
	ERROR_ON_PHILO_CREATION,
};

typedef struct s_state		t_state;
struct s_state
{
	t_input			input;
	t_philo			*philos;
	t_fork			*forks;
	t_error_state	error;
	pthread_mutex_t	print_mutex;
};

t_state	create_state(int input_data[5]);

#endif
