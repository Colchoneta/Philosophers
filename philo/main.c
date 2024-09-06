/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:15:35 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/06 11:23:05 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	if ((argc != 5) && (argc != 6))
		return (EXIT_FAILURE);
	if (check_arguments(argc, argv))
		return (EXIT_FAILURE);
	if (init_data(&data, argc, argv))
		return (EXIT_FAILURE);
	if (data.n_philos == 1)
		return (start_thread(&data));
	if (start_threads(&data))
		return (1);
	ft_exit(&data);
	return (0);
}
