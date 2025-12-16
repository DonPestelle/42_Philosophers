/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:36:51 by pestell2          #+#    #+#             */
/*   Updated: 2025/12/10 14:20:20 by pestell2         ###   ########.fr       */
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
		return (print_error(ARGUMENTS_NUMBER));
	i = 1;
	while (i < argc)
	{
		if (check_format(argv[i]))
			return (print_error(ARGS_NOT_NUMERIC));
		val[i - 1] = ft_atol(argv[i]);
		if (val[i - 1] <= 0 || val[i - 1] > INT_MAX)
			return (print_error(NEGATIVE_NUMBERS));
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
