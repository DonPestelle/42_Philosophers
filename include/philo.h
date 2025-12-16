/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:40:22 by pestell2          #+#    #+#             */
/*   Updated: 2025/12/10 14:20:06 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef enum e_error
{
	ARGUMENTS_NUMBER,
	ARGS_NOT_NUMERIC,
	NEGATIVE_NUMBERS,
	CREATING_VARIABLES,
	CREATING_THREADS,
}	t_error;

typedef enum e_messages
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	FINISH_MEALS,
	DIE
}	t_messages;

struct s_philo
{
	int				id;
	pthread_t		thread;
	int				left_fork;
	int				right_fork;
	long			last_meal;
	t_data			*data;
	pthread_mutex_t	philo_mutex;
	int				meals_done;
	bool			is_eating;
};

struct s_data
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	pthread_t		monitor_thread;
	int				stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	long			start_time;
};

/* args.c */
int		parse_args(int argc, char **argv);
t_data	*get_data_instance(void);

/* errors.c */
int		print_error(t_error err);

/* philos.c */
void	init_philos(t_data *data);
void	cleanup_philos(t_data *data);

/* philo_actions.c */
void	*philo_routine(void *arg);

/* monitor.c */
void	*monitor(void *arg);

/* messg.c */
void	ft_display_message(t_messages msg, t_philo *philo);

/* utils.c */
long	ft_atol(const char *str);
int		ft_strlen(const char *str);
long	ft_get_time(void);
void	ft_assign_values(long val[], int has_meals);
void	ft_sleep(long ms, t_data *data);

#endif
