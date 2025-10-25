/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:03:10 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/25 18:43:36 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "philo.h"
# include <stdio.h>

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

#endif
