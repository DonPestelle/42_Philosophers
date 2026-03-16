/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:43:22 by pestell2          #+#    #+#             */
/*   Updated: 2026/03/16 16:45:26 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define STR_EAT "is eating"
# define STR_SLEEP "is sleeping"
# define STR_THINK "is thinking"
# define STR_FORK "has taken a fork"
# define STR_DIE "died"

typedef pthread_mutex_t	t_mutex;

typedef struct s_info
{
	long	start_time;
	long	n_philo;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	long	max_eat;
	int		*end;
	t_mutex	*print;
	t_mutex	*dead;
	t_mutex	*meal;
}	t_info;

typedef struct s_philo
{
	int			id;
	int			meals_count;
	long		last_meal;
	pthread_t	thread;
	t_mutex		*l_fork;
	t_mutex		*r_fork;
	t_info		*info;
}	t_philo;

typedef struct s_table
{
	t_philo	*philos;
	t_mutex	*forks;
	t_mutex	print_m;
	t_mutex	dead_m;
	t_mutex	meal_m;
	t_info	info;
}	t_table;

/* --- PROTOTIPOS (Esto es lo que falta) --- */

// init.c
int		init_all(t_table *t, int ac, char **av);
void	cleanup(t_table *t);

// utils.c
long	get_time(void);
void	ft_usleep(long ms, t_info *info);
void	print_state(t_philo *p, char *str);

// routine.c
void	*philo_life(void *arg);

// monitor.c
void	monitor_philos(t_table *t);
#endif
