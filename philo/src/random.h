/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:44:01 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/24 17:48:38 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_H
# define RANDOM_H

typedef struct s_philo	t_philo;
struct s_philo
{
	int	philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_limit;
};

#endif
