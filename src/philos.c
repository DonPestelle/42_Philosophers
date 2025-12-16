/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:14:05 by pestell2          #+#    #+#             */
/*   Updated: 2025/12/10 14:21:07 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	if (!data->forks)
		return ;
	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

static void	init_philos_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].meals_done = 0;
		data->philos[i].is_eating = false;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->number_of_philos;
		pthread_mutex_init(&data->philos[i].philo_mutex, NULL);
		i++;
	}
}

void	init_philos(t_data *data)
{
	if (!data)
		return ;
	data->philos = malloc(sizeof(t_philo) * data->number_of_philos);
	if (!data->philos)
	{
		data->philos = NULL;
		return ;
	}
	init_forks(data);
	if (!data->forks)
	{
		free(data->philos);
		data->philos = NULL;
		return ;
	}
	init_philos_data(data);
}

void	cleanup_philos(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->philos)
	{
		i = 0;
		while (i < data->number_of_philos)
		{
			pthread_mutex_destroy(&data->philos[i].philo_mutex);
			i++;
		}
		free(data->philos);
		data->philos = NULL;
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->number_of_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
}
