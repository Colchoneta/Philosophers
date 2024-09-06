/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:15:34 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/05 20:57:52 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_argument(char *arg)
{
	int	i;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (ft_error(ERR_INPUT_1, NULL));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_arguments(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (check_argument(argv[i]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
