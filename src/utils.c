/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:35:26 by pestell2          #+#    #+#             */
/*   Updated: 2025/12/10 14:20:59 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atol(const char *str)
{
	long	result;

	result = 0;
	if (*str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LONG_MAX - (*str - '0')) / 10)
			return (LONG_MAX);
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long	ft_get_time(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

void	ft_assign_values(long val[], int has_meals)
{
	t_data	*data;

	data = get_data_instance();
	data->number_of_philos = (int)val[0];
	data->time_to_die = (int)val[1];
	data->time_to_eat = (int)val[2];
	data->time_to_sleep = (int)val[3];
	if (has_meals)
		data->number_of_meals = (int)val[4];
	else
		data->number_of_meals = -1;
	data->stop = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	data->philos = NULL;
	data->forks = NULL;
	data->start_time = ft_get_time();
}

void	ft_sleep(long ms, t_data *data)
{
	long	start;

	start = ft_get_time();
	while (!data->stop)
	{
		if (ft_get_time() - start >= ms)
			break ;
		usleep(200);
	}
}
