/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:22:27 by timtan            #+#    #+#             */
/*   Updated: 2026/08/22 17:32:01 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */
/*                              Libraries                                     */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>


/* ************************************************************************** */
/*                               Structs                                      */
/* ************************************************************************** */

/*
 * Struct to store shared data (input & mutexes).
 */
typedef struct s_data
{
	size_t			num_of_philo;
	size_t			ttd;
	size_t			tte;
	size_t			tts;
	size_t			num_of_eat;
	size_t			end_sim;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	end_sim_lock;
}					t_data;

/*
 * Struct to store crucial information for each philosopher
 */
typedef struct s_philo
{
	t_data			*data;
	pthread_t		thread;
	size_t			position;
	size_t			dead;
	size_t			eating;
	size_t			last_eaten;
	size_t			times_eaten;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	eaten_lock;
	pthread_mutex_t	last_eat_lock;
}					t_philo;

/* ************************************************************************** */
/*                            Function Prototypes                             */
/* ************************************************************************** */

// ft_atol.c
long		ft_atol(const char *nptr);

// time.c
void		msleep(int ms);
long long	current_time_in_ms(void);

// init.c
int			init_program(t_data *data, t_philo **philos, int ac, char **av);

// cleanup.c
void		cleanup(t_data *data, t_philo **philos, int f_created, int p_created);

// thread.c
int			start_threads(t_data *data, t_philo **philos);

// print_log.c
void		print_log(t_philo *philo, char *message);

// routine.c
void		*philo_routine(void *arg);

//attend.c
void		*attend(void *arg);

#endif
