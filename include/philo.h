/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestell2 <pestelle.official@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:40:22 by pestell2          #+#    #+#             */
/*   Updated: 2025/11/10 17:14:50 by pestell2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

 #include <unistd.h>
 #include <stdio.h>
 #include <pthread.h>
 #include <stdlib.h>
 #include <limits.h>
 #define  ERR_ARGS "Error: Invalid number of arguments.\n"
 #define  ERR_VAL "Error: Arguments must be positive integers.\n"
 typedef struct s_philo t_philo;
 typedef struct s_data
 {
    int            number_of_philosophers;
    int            time_to_die;
    int            time_to_eat;
    int            time_to_sleep;
    int            number_of_meals;
    int            n;
    pthread_mutex_t *forks;
    t_philo        *philos;
    long           start_time;
    pthread_mutex_t print_mutex;
 }              t_data;
 typedef struct s_philo
 {
    int             id;
    pthread_t       thread;
    int             left;
    int             right;
    long            last_meal;
    t_data         *data;
 }             t_philo;

 //____________________SRC____________________//
void  *philo_routine(void *arg);

//____________________ARGS____________________//
int    parse_args(int argc, char **argv);
void   ft_assign_values(long *val, int has_meals);
t_data *get_data_instance();

//____________________ERRORS____________________//
int    print_error(char *msg);

//____________________UTILS____________________//
long   ft_atol(const char *str);
int    ft_strlen(const char *str);

//_____________________PHILOS____________________//
int   create_philos(t_data *d);
void  join_threads(t_data *d);
 #endif