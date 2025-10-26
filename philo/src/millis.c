/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   millis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:33:04 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/26 16:38:59 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "millis.h"

unsigned long	millis(void)
{
	struct timeval	timeofday;
	unsigned long	sec_to_millis;
	unsigned long	micro_to_millis;
	unsigned long	millis;

	gettimeofday(&timeofday, 0);
	sec_to_millis = timeofday.tv_sec * 1000;
	micro_to_millis = timeofday.tv_usec / 1000;
	millis = sec_to_millis + micro_to_millis;
	return (millis);
}
