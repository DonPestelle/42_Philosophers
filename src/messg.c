/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:20:00 by pestell2          #+#    #+#             */
/*   Updated: 2025/12/10 14:21:24 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	should_print(t_data *data, t_messages msg)
{
	if (msg == DIE)
		return (1);
	if (data->stop)
		return (0);
	return (1);
}

void	ft_display_message(t_messages msg, t_philo *philo)
{
	t_data	*data;
	long	time;

	if (!philo)
		return ;
	data = philo->data;
	if (!should_print(data, msg))
		return ;
	pthread_mutex_lock(&data->print_mutex);
	time = ft_get_time() - data->start_time;
	if (msg == FORK)
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if (msg == EAT)
		printf("%ld %d is eating\n", time, philo->id);
	else if (msg == SLEEP)
		printf("%ld %d is sleeping\n", time, philo->id);
	else if (msg == THINK)
		printf("%ld %d is thinking\n", time, philo->id);
	else if (msg == FINISH_MEALS)
		printf("%ld All philosophers have finished their meals!\n", time);
	else if (msg == DIE)
		printf("%ld %d died\n", time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
}
