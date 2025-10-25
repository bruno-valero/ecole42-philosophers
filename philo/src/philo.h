/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:24:38 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/25 16:28:58 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_fork			t_fork;
struct s_fork
{
	t_fork			*self_ref;
	int				id;
	pthread_mutex_t	mutex;
	int				is_used_by;
	int				error;
	void			(*destroy)(t_fork fork);
};

typedef struct s_philo			t_philo;
struct s_philo
{
	t_philo		*self_ref;
	int			id;
	pthread_t	thread;
	t_fork		right_fork;
	t_fork		left_fork;
	int			is_eating;
	int			error;
	void		*(*stop)(t_philo *philo);
};

#endif
