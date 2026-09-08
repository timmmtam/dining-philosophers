/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:55:22 by timtan            #+#    #+#             */
/*   Updated: 2026/09/08 09:43:18 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Parsing the input and verifying integrity
 * Time to die, eat, sleep and number of philo cannot be 0
 */
static int	init_data(t_data *data, int ac, char **av)
{
	data->num_of_philo = ft_atoz(av[1]);
	if (data->num_of_philo <= 0)
		return (printf("Error: Invalid number of philosophers.\n"), 1);
	data->ttd = ft_atoz(av[2]);
	if (data->ttd <= 0)
		return (printf("Error: Invalid time to die.\n"), 1);
	data->tte = ft_atoz(av[3]);
	if (data->tte <= 0)
		return (printf("Error: Invalid time to eat.\n"), 1);
	data->tts = ft_atoz(av[4]);
	if (data->tts <= 0)
		return (printf("Error: Invalid time to sleep.\n"), 1);
	if (ac == 6)
	{
		data->num_of_eat = ft_atoz(av[5]);
		if (data->num_of_eat <= 0)
			return (printf("Error: Invalid eat count.\n"), 1);
	}
	data->end_sim = 0;
	return (0);
}

/*
 * Initializes mutexes in data struct.
 * 1 mutex for each fork (1 fork cannot be used by two philo at the same time)
 * 1 mutex for reading and writing the end_sim variable.
 * 1 mutex for reading and writing the sart_sim variable.
 */
static int	init_mutexes(t_data *data)
{
	size_t	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
		return (printf("Error: Forks malloc failed.\n"), -1);
	if (pthread_mutex_init(&data->end_sim_lock, NULL) != 0)
		return (printf("Error: Mutex creation failed.\n"), -2);
	if (pthread_mutex_init(&data->start_lock, NULL) != 0)
		return (printf("Error: Mutex creation failed.\n"), -3);
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (printf("Error: Mutex creation failed.\n"), i);
		i++;
	}
	return (0);
}

/*
 * Creating and storing each philosopher in a 2D array (array of pointers).
 * Left and right forks are assigned depending on the philopher's position.
 * The index corresponding with the philo will be the right fork.
 */
static int	init_philos(t_philo **philos, const t_data *data)
{
	size_t	i;

	i = 0;
	*philos = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!(*philos))
		return (printf("Error: Philos malloc failed.\n"), -1);
	while (i < data->num_of_philo)
	{
		(*philos)[i] = (t_philo){0};
		(*philos)[i].position = i;
		(*philos)[i].data = (t_data *)data;
		(*philos)[i].last_eaten = current_time_in_ms();
		(*philos)[i].right_fork = &data->forks[i];
		if (i == 0)
			(*philos)[i].left_fork = &data->forks[data->num_of_philo - 1];
		else
			(*philos)[i].left_fork = &data->forks[i - 1];
		if (pthread_mutex_init(&(*philos)[i].eaten_lock, NULL) != 0)
			return (i);
		if (pthread_mutex_init(&(*philos)[i].last_eat_lock, NULL) != 0)
			return (pthread_mutex_destroy(&(*philos)[i].eaten_lock), i);
		i++;
	}
	return (0);
}

/*
 * Main init function that calls all the other init functions
 * Calls cleanup if an init function fails
 */
int	init_program(t_data *data, t_philo **philos, int ac, char **av)
{
	int	error_code;

	if (init_data(data, ac, av))
		return (1);
	error_code = init_mutexes(data);
	if (error_code)
	{
		if (error_code == -1 || error_code == -2)
			return (1);
		else if (error_code == -3)
			pthread_mutex_destroy(&data->end_sim_lock);
		else
			cleanup(data, philos, error_code, 0);
		return (1);
	}
	error_code = init_philos(philos, data);
	if (error_code)
	{
		if (error_code == -1)
			cleanup(data, philos, data->num_of_philo, 0);
		else
			cleanup(data, philos, data->num_of_philo, error_code);
		return (1);
	}
	return (0);
}
