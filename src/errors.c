/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:52:10 by pestell2          #+#    #+#             */
/*   Updated: 2025/12/10 14:20:32 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	print_error(t_error err)
{
	if (err == ARGUMENTS_NUMBER)
		printf("Error: Incorrect number of arguments.\n");
	else if (err == ARGS_NOT_NUMERIC)
		printf("Error: All arguments must be positive integers.\n");
	else if (err == NEGATIVE_NUMBERS)
		printf("Error: Arguments must be greater than zero"
			" and within valid range.\n");
	else if (err == CREATING_VARIABLES)
		printf("Error: Failed to create necessary variables.\n");
	else if (err == CREATING_THREADS)
		printf("Error: Failed to create threads.\n");
	else
		printf("Error: An unknown error occurred.\n");
	return (1);
}
