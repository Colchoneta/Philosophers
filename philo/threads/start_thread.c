/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:17:13 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/05 20:54:14 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	start_thread(t_data *data)
{
	data->start_time = ft_get_time();
	if (pthread_create(&data->thread_ids[0], NULL, &routine, &data->philos[0]))
		return (ft_error(ERR_THREAD, data));
	pthread_detach(data->thread_ids[0]);
	while (data->dead == 0)
		ft_usleep(0);
	ft_exit(data);
	return (0);
}
