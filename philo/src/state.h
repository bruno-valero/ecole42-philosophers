/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:44:01 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/31 16:09:19 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# include <stdlib.h>
# include "philo.h"
# include "monitor.h"

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
	ERROR_ON_PRINT_MUTEXT_CREATION,
	ERROR_ON_DEAD_MUTEXT_CREATION,
	ERROR_ON_MONITOR_CREATION,
};

typedef struct s_state		t_state;
struct s_state
{
	pthread_t		*monitor;
	long long		start_time;
	t_input			input;
	t_philo			**philos;
	t_fork			**forks;
	int				error;
	pthread_mutex_t	*everyone_ate_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*dead_mutex;
	long long		someone_died;
	int				every_one_ate;
};

t_create_philo	params_philo(int id, t_state *state);
int				init_state_mutexes(t_state *state);
t_state			create_state(int input_data[5]);

#endif
