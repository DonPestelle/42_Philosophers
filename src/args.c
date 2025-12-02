/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:36:51 by pestell2          #+#    #+#             */
/*   Updated: 2025/11/13 15:35:37 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_format(const char *p)
{
	if (*p == '+')
		p++;
	if (*p == '\0')
		return (1);
	while (*p)
	{
		if (*p < '0' || *p > '9')
			return (1);
		p++;
	}
	return (0);
}

int	parse_args(int argc, char **argv)
{
	int		i;
	long	val[5];

	if (argc < 5 || argc > 6)
		return (print_error(ERR_ARGS));
	i = 1;
	while (i < argc)
	{
		if (check_format(argv[i]))
			return (print_error(ERR_VAL));
		val[i - 1] = ft_atol(argv[i]);
		if (val[i - 1] <= 0 || val[i - 1] > INT_MAX)
			return (print_error(ERR_VAL));
		i++;
	}
	ft_assign_values(val, argc == 6);
	return (0);
}

t_data	*get_data_instance(void)
{
	static t_data	data;

	return (&data);
}

void	ft_assign_values(long *val, int has_meals)
{
	t_data	*data;

	data = get_data_instance();
	data->number_of_philosophers = (int)val[0];
	data->time_to_die = (int)val[1];
	data->time_to_eat = (int)val[2];
	data->time_to_sleep = (int)val[3];
	if (has_meals)
		data->number_of_meals = (int)val[4];
	else
		data->number_of_meals = -1;
}
