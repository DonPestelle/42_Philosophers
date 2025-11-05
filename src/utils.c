/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:16:43 by pestell2          #+#    #+#             */
/*   Updated: 2025/11/05 14:35:50 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long    ft_atol(const char *str)
{
    long    result;

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