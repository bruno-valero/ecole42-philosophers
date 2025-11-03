/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:15:42 by brunofer          #+#    #+#             */
/*   Updated: 2025/11/03 18:01:38 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	int		*input_data;
	t_state	state;

	if (argc == 1)
		return (1);
	if (argc < 5 || argc > 6)
	{
		printf("invalid input!\n");
		return (1);
	}
	input_data = validate_arguments(argc, argv);
	if (!input_data)
	{
		printf("invalid input!\n");
		return (1);
	}
	state = create_state(input_data);
}
