/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:51:58 by pestell2          #+#    #+#             */
/*   Updated: 2026/03/13 14:52:00 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_table *t)
{
	int	i;

	t->forks = malloc(sizeof(t_mutex) * t->info.n_philo);
	if (!t->forks)
		return (1);
	i = 0;
	while (i < t->info.n_philo)
	{
		if (pthread_mutex_init(&t->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&t->print_m, NULL))
		return (1);
	if (pthread_mutex_init(&t->dead_m, NULL))
		return (1);
	if (pthread_mutex_init(&t->meal_m, NULL))
		return (1);
	return (0);
}

static void	assign_philos(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->info.n_philo)
	{
		t->philos[i].id = i;
		t->philos[i].meals_count = 0;
		t->philos[i].info = &t->info;
		t->philos[i].last_meal = get_time();
		t->philos[i].l_fork = &t->forks[i];
		t->philos[i].r_fork = &t->forks[(i + 1) % t->info.n_philo];
		i++;
	}
}

int	init_all(t_table *t, int ac, char **av)
{
	t->info.n_philo = atol(av[1]);
	t->info.t_die = atol(av[2]);
	t->info.t_eat = atol(av[3]);
	t->info.t_sleep = atol(av[4]);
	t->info.max_eat = -1;
	if (ac == 6)
		t->info.max_eat = atol(av[5]);
	t->info.end = malloc(sizeof(int));
	if (!t->info.end)
		return (1);
	*t->info.end = 0;
	t->info.print = &t->print_m;
	t->info.dead = &t->dead_m;
	t->info.meal = &t->meal_m;
	t->philos = malloc(sizeof(t_philo) * t->info.n_philo);
	if (!t->philos || init_mutexes(t))
		return (1);
	assign_philos(t);
	return (0);
}

void	cleanup(t_table *t)
{
	int	i;

	if (t->forks)
	{
		i = 0;
		while (i < t->info.n_philo)
			pthread_mutex_destroy(&t->forks[i++]);
		free(t->forks);
	}
	if (t->philos)
		free(t->philos);
	if (t->info.end)
		free(t->info.end);
	pthread_mutex_destroy(&t->print_m);
	pthread_mutex_destroy(&t->dead_m);
	pthread_mutex_destroy(&t->meal_m);
}
