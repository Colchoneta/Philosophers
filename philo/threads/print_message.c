/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:46:08 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/06 12:56:48 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_message(char *msg, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = ft_get_time() - philo->data->start_time;
	if (ft_strcmp(DIE, msg) == 0 && philo->data->dead == 0)
	{
		printf("%lu %d %s\n", time, philo->id, msg);
		pthread_mutex_lock(&philo->data->lock);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->lock);
	}
	if (!philo->data->dead)
		printf("%lu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->write);
}
