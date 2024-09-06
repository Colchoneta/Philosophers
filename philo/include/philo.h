/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:15:42 by angcampo          #+#    #+#             */
/*   Updated: 2024/09/05 21:28:12 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <string.h>

//exit
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

//input error
# define ERR_INPUT_1 "Incorrect input character"
# define ERR_INPUT_2 "Incorrect input value"

//calloc error
# define ERR_CALLOC_1 "Error while allocating data->thread_ids"
# define ERR_CALLOC_2 "Error while allocating data->philos"
# define ERR_CALLOC_3 "Error while allocating data->forks"

//thread errors
# define ERR_THREAD "Error while creating a thread"
# define ERR_JOIN "Error while joining a thread"

//messages
# define TAKE "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread_supervisor;
	int				id;
	int				meals_eaten;
	int				status;
	int				eating;
	u_int64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*thread_ids;
	int				n_philos;
	int				n_meals;
	int				dead;
	int				finished_philos;
	t_philo			*philos;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

//utils
int			ft_atoi(char *str);
void		*ft_calloc(size_t count, size_t size);
int			ft_error(char *str, t_data *data);
void		ft_exit(t_data *data);
u_int64_t	ft_get_time(void);
int			ft_isdigit(int c);
int			ft_isspace(int c);
int			ft_strcmp(char *s1, char *s2);
int			ft_usleep(u_int64_t time);

//initalization
int			check_arguments(int argc, char **argv);
int			init_data(t_data *data, int argc, char **argv);

//threads execution
void		action(t_philo *philo);
void		print_message(char *msg, t_philo *philo);
int			start_thread(t_data *data);
void		*routine(void *philo_pointer);
int			start_threads(t_data *data);

#endif
