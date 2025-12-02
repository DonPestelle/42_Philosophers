/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:08:20 by pestell2          #+#    #+#             */
/*   Updated: 2025/11/13 18:00:59 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return (print_error("Memory allocation failed"));
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left = i;
		data->philos[i].right = (i + 1) % data->number_of_philosophers;
		data->philos[i].data = data;
		data->philos[i].last_meal = current_time_ms();
		data->philos[i].meals_done = 0;
		i++;
	}
	return (0);
}

static void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	pthread_t	monitor_thread;

	data = get_data_instance();
	data->stop = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	if (parse_args(argc, argv))
		return (1);
	if (init_philos(data))
		return (1);
	create_philos(data);
	pthread_create(&monitor_thread, NULL, monitor, data);
	join_threads(data);
	pthread_join(monitor_thread, NULL);
	cleanup(data);
	return (0);
}
