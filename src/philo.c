/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:08:20 by codespace         #+#    #+#             */
/*   Updated: 2025/11/05 11:02:19 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    *to_do_list(void *philo)
{
    int id = *(int*)philo;
    printf("hello, i'm philo [%d]\n", id); 
    pthread_exit(NULL);
}

int     main()
{
    int number_of_philosophers = 3;
    pthread_t philo[number_of_philosophers];
    int ids[number_of_philosophers];
    int i;

    i = 0;
    while (i++ < number_of_philosophers)
    {
       ids[i] = i;  // guardamos el id por separado
        if (pthread_create(&philo[i], NULL, to_do_list, &ids[i]) != 0) {
            perror("Error al crear hilo");
            return 1;
        }
    }
    i = 0;
    while (i++ < number_of_philosophers)
    {
      if (pthread_join(philo[i], NULL) != 0){
            perror("error al final\n");
            return 0;
         }
    }
}