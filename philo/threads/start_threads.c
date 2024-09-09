/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:41:54 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/09 20:35:28 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*monitor(void *philo_pointer)
{
	t_philo	*philo;
	int		dead;

	philo = (t_philo *)philo_pointer;
	pthread_mutex_lock(&philo->data->lock);
	dead = philo->data->dead;
	pthread_mutex_unlock(&philo->data->lock);
	while (!dead)
	{
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finished_philos >= philo->data->n_philos)
			philo->data->dead = 1;
		dead = philo->data->dead;
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

static void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;
	int		dead;

	philo = (t_philo *)philo_pointer;
	pthread_mutex_lock(&philo->data->lock);
	dead = philo->data->dead;
	pthread_mutex_unlock(&philo->data->lock);
	while (!dead)
	{
		pthread_mutex_lock(&philo->lock);
		if (ft_get_time() >= philo->time_to_die && philo->eating == 0)
			print_message(DIE, philo);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->meals_eaten == philo->data->n_meals)
			philo->data->finished_philos++;
		dead = philo->data->dead;
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)EXIT_SUCCESS);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;
	int		dead;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = philo->data->time_to_die + ft_get_time();
	if (pthread_create(&philo->thread_supervisor,
			NULL, &supervisor, philo_pointer))
		return ((void *)EXIT_FAILURE);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat/10);
	dead = 0;
	while (dead == 0)
	{
		action(philo);
		pthread_mutex_lock(&philo->data->lock);
		dead = philo->data->dead;
		pthread_mutex_unlock(&philo->data->lock);
	}
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
