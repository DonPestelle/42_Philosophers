/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:08:20 by pestell2          #+#    #+#             */
/*   Updated: 2025/12/10 14:21:59 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			return (print_error(CREATING_THREADS));
		i++;
	}
	if (pthread_create(&data->monitor_thread, NULL, monitor, data) != 0)
		return (print_error(CREATING_THREADS));
	return (0);
}

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor_thread, NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (parse_args(argc, argv))
		return (1);
	data = get_data_instance();
	init_philos(data);
	if (!data->philos)
		return (print_error(CREATING_VARIABLES));
	if (start_threads(data))
	{
		cleanup_philos(data);
		return (1);
	}
	join_threads(data);
	cleanup_philos(data);
	return (0);
}
