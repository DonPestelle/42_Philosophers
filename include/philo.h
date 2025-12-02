/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:40:22 by pestell2          #+#    #+#             */
/*   Updated: 2025/12/02 12:41:00 by pestell2         ###   ########.fr       */
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

# define ERR_ARGS "Invalid number of arguments.\n"
# define ERR_VAL "Arguments must be positive integers.\n"

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				left;
	int				right;
	long			last_meal;
	t_data			*data;
	int				meals_done;
	int 				is_eating;
}		t_philo;

typedef struct	 s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
}	t_data;

//====================== ARGS ======================//
int		parse_args(int argc, char **argv);
void	ft_assign_values(long *val, int has_meals);
t_data	*get_data_instance(void);

//====================== ERRORS ====================//
int		print_error(char *msg);

//====================== UTILS =====================//
long	ft_atol(const char *str);
long	current_time_ms(void);

//===================== PHILOS =====================//
int		create_philos(t_data *data);
void	join_threads(t_data *data);
void	*philo_routine(void *arg);
void	*monitor(void *arg);

#endif
