/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:51:01 by pestell2          #+#    #+#             */
/*   Updated: 2026/03/16 16:46:02 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_routine(t_philo *p)
{
	pthread_mutex_lock(p->l_fork);
	print_state(p, "has taken a fork");
	if (p->info->n_philo == 1)
	{
		ft_usleep(p->info->t_die, p->info);
		pthread_mutex_unlock(p->l_fork);
		return ;
	}
	pthread_mutex_lock(p->r_fork);
	print_state(p, "has taken a fork");
	print_state(p, "is eating");
	pthread_mutex_lock(p->info->meal);
	p->last_meal = get_time();
	p->meals_count++;
	pthread_mutex_unlock(p->info->meal);
	ft_usleep(p->info->t_eat, p->info);
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}

void	*philo_life(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2)
		usleep(15000);
	while (1)
	{
		pthread_mutex_lock(p->info->dead);
		if (*p->info->end)
		{
			pthread_mutex_unlock(p->info->dead);
			break ;
		}
		pthread_mutex_unlock(p->info->dead);
		eat_routine(p);
		print_state(p, "is sleeping");
		ft_usleep(p->info->t_sleep, p->info);
		print_state(p, "is thinking");
	}
	return (NULL);
}
