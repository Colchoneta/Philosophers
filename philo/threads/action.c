/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:51:16 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/06 10:26:06 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_message(TAKE, philo);
	pthread_mutex_lock(philo->r_fork);
	print_message(TAKE, philo);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = ft_get_time() + philo->data->time_to_die;
	print_message(EAT, philo);
	philo->meals_eaten++;
	ft_usleep(philo->data->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_message(SLEEP, philo);
	ft_usleep(philo->data->time_to_sleep);
}

static void	think(t_philo *philo)
{
	print_message(THINK, philo);
}

void	action(t_philo *philo)
{
	take_forks(philo);
	eat(philo);
	drop_forks(philo);
	think(philo);
}
