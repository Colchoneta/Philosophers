/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:17:13 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/06 13:47:03 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	start_thread(t_data *data)
{
	int	dead;

	data->start_time = ft_get_time();
	if (pthread_create(&data->thread_ids[0], NULL, &routine, &data->philos[0]))
		return (ft_error(ERR_THREAD, data));
	pthread_detach(data->thread_ids[0]);
	dead = 0;
	while (dead == 0)
	{
		ft_usleep(0);
		pthread_mutex_lock(&data->lock);
		dead = data->dead;
		pthread_mutex_unlock(&data->lock);
	}
	ft_exit(data);
	return (0);
}
