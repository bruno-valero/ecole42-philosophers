/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunofer <brunofer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:07:33 by brunofer          #+#    #+#             */
/*   Updated: 2025/10/25 14:59:30 by brunofer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validate_input.h"

static int				is_number(char *str);
static int				is_less_than_ulong(char *str);
static unsigned long	atoul(char *str);
static int				validate_input(char *input);


int	*validate_arguments(int argc, char **argv)
{
	int	*result;
	int	i;

	result = malloc(5 * sizeof(int));
	i = 0;
	while (++i < argc)
	{
		result[i - 1] = validate_input(argv[i]);
		if (i - 1 == 4 && result[i - 1] >= 0)
			continue ;
		else if (i - 1 < 4 && result[i - 1] == 0)
			result[i - 1] = -1;
		if (result[i - 1] < 0)
		{
			free(result);
			return (NULL);
		}
	}
	if (argc == 5)
		result[4] = -1;
	return (result);
}

static int	validate_input(char *input)
{
	unsigned long	result;

	if (!is_number(input))
		return (-1);
	if (!is_less_than_ulong(input))
		return (-1);
	result = atoul(input);
	if (result > INT_MAX)
		return (-1);
	return ((int)result);
}

static int	is_number(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if ((str[i] < '0' && str[i] > '9') || str[i] == ' ')
			return (0);
	return (1);

}

static int	is_less_than_ulong(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	i++;
	return (i <= 19);
}

static unsigned long	atoul(char *str)
{
	unsigned long	result;
	int				i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	result = 0;
	while (str[i] && str[i] != ' ')
		result = result * 10 + (str[i++] - '0');
	return (result);
}
