/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:08:20 by codespace         #+#    #+#             */
/*   Updated: 2025/11/10 17:13:12 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *philo_routine(void *arg) {
    int id = *(int *)arg;
    printf("Soy philo%d\n", id);
    free(arg);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (parse_args(argc, argv) != 0)
        return 1;
    pthread_t *threads = malloc(sizeof(pthread_t) * get_data_instance()->number_of_philosophers);
    create_philos(get_data_instance());
    join_threads(get_data_instance());
    free(threads);
    return 0;
}
