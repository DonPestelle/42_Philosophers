/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:32:25 by pestell2          #+#    #+#             */
/*   Updated: 2025/12/10 14:21:45 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	take_forks(t_philo *philo)
{
	t_data	*data;
	int		first;
	int		second;
	int		tmp;

	data = philo->data;
	first = philo->left_fork;
	second = philo->right_fork;
	if (first > second)
	{
		tmp = first;
		first = second;
		second = tmp;
	}
	pthread_mutex_lock(&data->forks[first]);
	ft_display_message(FORK, philo);
	pthread_mutex_lock(&data->forks[second]);
	ft_display_message(FORK, philo);
}

static void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->number_of_philos == 1)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		ft_display_message(FORK, philo);
		ft_sleep(data->time_to_die, data);
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		return ;
	}
	take_forks(philo);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->is_eating = true;
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->philo_mutex);
	ft_display_message(EAT, philo);
	ft_sleep(data->time_to_eat, data);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->is_eating = false;
	philo->meals_done++;
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
}

static void	philo_sleep(t_philo *philo)
{
	ft_display_message(SLEEP, philo);
	ft_sleep(philo->data->time_to_sleep, philo->data);
}

static void	philo_think(t_philo *philo)
{
	ft_display_message(THINK, philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!data->stop)
	{
		philo_eat(philo);
		if (data->stop)
			break ;
		if (data->number_of_meals != -1
			&& philo->meals_done >= data->number_of_meals)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
