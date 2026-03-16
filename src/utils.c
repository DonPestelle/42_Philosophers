/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:50:38 by pestell2          #+#    #+#             */
/*   Updated: 2026/03/16 17:19:47 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long ms, t_info *info)
{
	long	start;

	start = get_time();
	while (1)
	{
		pthread_mutex_lock(info->dead);
		if (*info->end)
		{
			pthread_mutex_unlock(info->dead);
			break ;
		}
		pthread_mutex_unlock(info->dead);
		if (get_time() - start >= ms)
			break ;
		usleep(200);
	}
}

void	print_state(t_philo *p, char *str)
{
	long	relative_time;

	pthread_mutex_lock(p->info->dead);
	if (!*p->info->end)
	{
		pthread_mutex_lock(p->info->print);
		relative_time = get_time() - p->info->start_time;
		printf("%ld %d %s\n", relative_time, p->id + 1, str);
		pthread_mutex_unlock(p->info->print);
	}
	pthread_mutex_unlock(p->info->dead);
}
