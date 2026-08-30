/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:55:22 by timtan            #+#    #+#             */
/*   Updated: 2026/08/30 14:34:21 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Parsing the input and verifying integrity
 * Time to die, eat, sleep and number of philo cannot be 0
 */
static int	init_data(t_data *data, int ac, char **av)
{
	if ((data->num_of_philo = ft_atoz(av[1])) <= 0)
		return (printf("Error. No. of philos is not greater than 0.\n"), 1);
	if ((data->ttd = ft_atoz(av[2])) <= 0)
		return (printf("Error. Time to die is not greater than 0.\n"), 1);
	if ((data->tte = ft_atoz(av[3])) <= 0)
		return (printf("Error. Time to eat is not greater than 0.\n"), 1);
	if ((data->tts = ft_atoz(av[4])) <= 0)
		return (printf("Error. Time to sleep is not greater 0.\n"), 1);
	if (ac == 6)
	{
		if ((data->num_of_eat = ft_atoz(av[5])) <= 0)
			return (printf("Error. Eat count is not greater than 0.\n"), 1);
	}
	data->end_sim = 0;
	return (0);
}

/*
 * Initializing all the mutexes
 * 1 mutex for each fork (1 fork cannot be used by two philo at the same time)
 * 1 mutex for printing status to the terminal so messages are not corrupt.
 * 1 mutex for reading and writing the is_dead variable.
 */
static int	init_mutexes(t_data *data)
{
	size_t	i;

	pthread_mutex_init(&data->end_sim_lock, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
		return (100);
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			return (i);
		}
		i++;
	}
	return(0);
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
		return (100);
	while (i < data->num_of_philo)
	{
		(*philos)[i] = (t_philo){0};
		(*philos)[i].position = i;
		(*philos)[i].data = (t_data *)data;
		(*philos)[i].last_eaten = current_time_in_ms();
		(*philos)[i].right_fork = data->forks[i];
		if (i == 0)
			(*philos)[i].left_fork = data->forks[data->num_of_philo - 1];
		else
			(*philos)[i].left_fork = data->forks[i - 1];
		pthread_mutex_init(&(*philos)[i].eaten_lock, NULL);
		pthread_mutex_init(&(*philos)[i].last_eat_lock, NULL);
		i++;
	}
	return(0);
}

/*
 * Main function that calls all the other init functions
 */
int	init_program(t_data *data, t_philo **philos, int ac, char **av)
{
	int	error_code;

	error_code = 0;
	if (init_data(data, ac, av))
		return (1);
	if ((error_code = init_mutexes(data)))
	{
		if (error_code == 100)
			printf("Malloc Failed\n");
		else
			cleanup(data, philos, error_code, 0);
		return (1);
	}
	if ((error_code = init_philos(philos, data)))
	{
		printf("Malloc Failed\n");
		cleanup(data, philos, data->num_of_philo, 0);
		return (1);
	}
	return (0);
}
