/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:32:25 by pestell2          #+#    #+#             */
/*   Updated: 2025/11/13 18:19:23 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

static void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	//if (philo->id % 2 == 0)
	//{
		pthread_mutex_lock(&data->forks[philo->right]);
		pthread_mutex_lock(&data->forks[philo->left]);
	//}
	//else
	//{
		//pthread_mutex_lock(&data->forks[philo->left]);
		//pthread_mutex_lock(&data->forks[philo->right]);
	//}
	pthread_mutex_lock(&data->print_mutex);
	philo->last_meal = current_time_ms();
	printf("Philo %d is eating 🍝\n", philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[philo->left]);
	pthread_mutex_unlock(&data->forks[philo->right]);
	philo->meals_done++;
}

static void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("Philo %d is sleeping 💤\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_sleep * 1000);
}

static void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("Philo %d is thinking 💭\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(500 * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!data->stop && (data->number_of_meals == -1
			|| philo->meals_done < data->number_of_meals))
	{
		if (data->stop)
			break;
		philo_eat(philo);
		if (data->stop)
			break;
		philo_sleep(philo);
		if (data->stop)
			break;
		philo_think(philo);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->stop)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->print_mutex);
			if ((current_time_ms() - data->philos[i].last_meal)
				> data->time_to_die)
			{
				printf("Philo %d died 💀\n", data->philos[i].id);
				data->stop = 1;
				pthread_mutex_unlock(&data->print_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->print_mutex);
			i++;
		}
		//usleep(1000);
	}
	return (NULL);
}
