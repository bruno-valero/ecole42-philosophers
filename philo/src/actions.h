/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:03:10 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/28 17:17:58 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include <stdio.h>
# include "millis.h"

typedef struct s_philo		t_philo;

typedef enum e_wich_fork	t_wich_fork;
enum e_wich_fork
{
	RIGHT_FORK,
	LEFT_FORK
};

typedef enum e_eat_state	t_eat_state;
enum e_eat_state
{
	START_TO_EAT,
	STOP_TO_EAT
};

typedef enum e_think_state	t_think_state;
enum e_think_state
{
	START_TO_THINK,
	STOP_TO_THINK
};

typedef enum e_sleep_state	t_sleep_state;
enum e_sleep_state
{
	START_TO_SLEEP,
	STOP_TO_SLEEP
};

void	get_fork(t_philo *philo, t_wich_fork wich_fork);
void	drop_fork(t_philo *philo, t_wich_fork wich_fork);
void	eat(t_philo *philo, t_eat_state eat_state);
void	think(t_philo *philo, t_think_state think_state);
void	ft_sleep(t_philo *philo, t_sleep_state sleep_state);
void	print_fok_state(
			t_philo *philo, t_wich_fork wich_fork, unsigned long time);
void	print_eatting(t_philo *philo);
void	print_sleeping(t_philo *philo, unsigned long time);
void	print_thinking(t_philo *philo, unsigned long time);
void	print_death(t_philo *philo);
t_philo	*verify_death(t_philo *philo);

#endif
