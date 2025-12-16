/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:32:25 by pestell2          #+#    #+#             */
/*   Updated: 2025/12/10 14:21:33 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_death(t_data *data)
{
	int		i;
	long	now;
	long	last_meal;

	i = 0;
	now = ft_get_time();
	while (i < data->number_of_philos)
	{
		pthread_mutex_lock(&data->philos[i].philo_mutex);
		last_meal = now - data->philos[i].last_meal;
		if (!data->philos[i].is_eating && last_meal > data->time_to_die)
		{
			pthread_mutex_unlock(&data->philos[i].philo_mutex);
			ft_display_message(DIE, &data->philos[i]);
			data->stop = 1;
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].philo_mutex);
		i++;
	}
	return (0);
}

static void	check_meals(t_data *data)
{
	int	i;
	int	all_done;

	if (data->number_of_meals == -1)
		return ;
	i = 0;
	all_done = 1;
	while (i < data->number_of_philos)
	{
		if (data->philos[i].meals_done < data->number_of_meals)
			all_done = 0;
		i++;
	}
	if (all_done)
	{
		ft_display_message(FINISH_MEALS, &data->philos[0]);
		data->stop = 1;
	}
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!data->stop)
	{
		if (check_death(data))
			return (NULL);
		check_meals(data);
		usleep(1000);
	}
	return (NULL);
}
