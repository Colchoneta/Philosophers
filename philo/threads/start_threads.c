/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:41:54 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/06 11:47:51 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*monitor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished_philos >= philo->data->n_philos)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

static void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (ft_get_time() >= philo->time_to_die && philo->eating == 0)
			print_message(DIE, philo);
		if (philo->meals_eaten == philo->data->n_meals)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished_philos++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)EXIT_SUCCESS);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = philo->data->time_to_die + ft_get_time();
	if (pthread_create(&philo->thread_supervisor,
			NULL, &supervisor, philo_pointer))
		return ((void *)EXIT_FAILURE);
	while (philo->data->dead == 0)
		action(philo);
	if (pthread_join(philo->thread_supervisor, NULL))
		return ((void *)EXIT_FAILURE);
	return ((void *)EXIT_SUCCESS);
}

int	start_threads(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	data->start_time = ft_get_time();
	if (data->n_meals > 0)
	{
		if (pthread_create(&monitor_thread,
				NULL, &monitor, &data->philos[0]))
			return (ft_error(ERR_THREAD, data));
	}
	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_create(&data->thread_ids[i],
				NULL, &routine, &data->philos[i]))
			return (ft_error(ERR_THREAD, data));
	}
	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_join(data->thread_ids[i], NULL))
			return (ft_error(ERR_JOIN, data));
	}
	return (0);
}
