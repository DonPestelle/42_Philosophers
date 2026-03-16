/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:51:26 by pestell2          #+#    #+#             */
/*   Updated: 2026/03/16 17:21:40 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *p)
{
	pthread_mutex_lock(p->info->meal);
	if (get_time() - p->last_meal >= p->info->t_die)
	{
		pthread_mutex_unlock(p->info->meal);
		print_state(p, "died");
		pthread_mutex_lock(p->info->dead);
		*p->info->end = 1;
		pthread_mutex_unlock(p->info->dead);
		return (1);
	}
	pthread_mutex_unlock(p->info->meal);
	return (0);
}

int	check_philosophers(t_table *t, int *all_finished)
{
	int	i;

	i = 0;
	*all_finished = 0;
	while (i < t->info.n_philo)
	{
		if (check_death(&t->philos[i]))
			return (1);
		pthread_mutex_lock(t->info.meal);
		if (t->info.max_eat != -1
			&& t->philos[i].meals_count >= t->info.max_eat)
			(*all_finished)++;
		pthread_mutex_unlock(t->info.meal);
		i++;
	}
	return (0);
}

void	monitor_philos(t_table *t)
{
	int	all_finished;

	while (1)
	{
		if (check_philosophers(t, &all_finished))
			return ;
		if (t->info.max_eat != -1 && all_finished == t->info.n_philo)
		{
			pthread_mutex_lock(t->info.dead);
			*t->info.end = 1;
			pthread_mutex_unlock(t->info.dead);
			return ;
		}
		usleep(1000);
	}
}
