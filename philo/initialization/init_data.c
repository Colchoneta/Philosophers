/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:42:51 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/06 11:43:13 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_arguments(t_data *data, int argc, char **argv)
{
	data->n_philos = (int)ft_atoi(argv[1]);
	data->time_to_die = (u_int64_t)ft_atoi(argv[2]);
	data->time_to_eat = (u_int64_t)ft_atoi(argv[3]);
	data->time_to_sleep = (u_int64_t)ft_atoi(argv[4]);
	if (argc == 6)
		data->n_meals = (int)ft_atoi(argv[5]);
	else
		data->n_meals = -1;
	if (data->n_philos <= 0 || data->n_philos > 200 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60)
		return (ft_error(ERR_INPUT_2, NULL));
	data->dead = 0;
	data->finished_philos = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (EXIT_SUCCESS);
}

static int	init_alloc_data(t_data *data)
{
	data->thread_ids = (pthread_t *)ft_calloc(sizeof(pthread_t),
			data->n_philos);
	if (!data->thread_ids)
		return (ft_error(ERR_CALLOC_1, data));
	data->philos = (t_philo *)ft_calloc(sizeof(t_philo),
			data->n_philos);
	if (!data->philos)
		return (ft_error(ERR_CALLOC_2, data));
	data->forks = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t),
			data->n_philos);
	if (!data->forks)
		return (ft_error(ERR_CALLOC_3, data));
	return (EXIT_SUCCESS);
}

static void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->time_to_die;
		pthread_mutex_init(&data->philos[i].lock, NULL);
	}
}

static void	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
	}
	i = 0;
	data->philos[i].l_fork = &data->forks[data->n_philos - 1];
	data->philos[i].r_fork = &data->forks[0];
	while (++i < data->n_philos)
	{
		data->philos[i].l_fork = &data->forks[i - 1];
		data->philos[i].r_fork = &data->forks[i];
	}
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (init_arguments(data, argc, argv))
		return (1);
	if (init_alloc_data(data))
		return (1);
	init_philos(data);
	init_forks(data);
	return (0);
}
