/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:14:05 by pestell2          #+#    #+#             */
/*   Updated: 2025/11/10 17:12:15 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int create_philos(t_data *d)
{
    int i;

    i = 0;
    while (i < d->n)
    {
        if (pthread_create(&d->philos[i].thread, NULL, philo_routine, &d->philos[i]) != 0)
        {
            int j = 0;
            while (j < i)
            {
                pthread_join(d->philos[j].thread, NULL);
                j++;
            }
            return (1); /* error */
        }
        i++;
    }
    return (0); /* ok */
}

void join_threads(t_data *d)
{
    int i;

    i = 0;
    while (i < d->n)
    {
        pthread_join(d->philos[i].thread, NULL);
        i++;
    }
}
