/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:46:29 by pestell2          #+#    #+#             */
/*   Updated: 2026/03/13 14:57:23 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	t;
	int		i;

	if (ac < 5 || ac > 6)
		return (printf("Error: Wrong args\n"), 1);
	if (init_all(&t, ac, av))
		return (1);
	t.info.start_time = get_time();
	i = 0;
	while (i < t.info.n_philo)
	{
		pthread_create(&t.philos[i].thread, NULL, philo_life, &t.philos[i]);
		i++;
	}
	monitor_philos(&t);
	i = 0;
	while (i < t.info.n_philo)
	{
		pthread_join(t.philos[i].thread, NULL);
		i++;
	}
	cleanup(&t);
	return (0);
}
