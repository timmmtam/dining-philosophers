/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:55:31 by timtan            #+#    #+#             */
/*   Updated: 2026/09/07 10:21:21 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Joins the created threads if a thread creation fails.
 * err variable is used to determine whether waitress or philo failed creation.
 */
int	thread_cleanup(t_philo **philos, int err)
{
	int	i;

	i = 0;
	if (err == -1)
		printf("Error: Thread creation failed for waitress.\n");
	else
	{
		printf("Error: Thread creation failed for philo.\n");
		pthread_mutex_lock(&(*philos)[0].data->end_sim_lock);
		(*philos)[0].data->end_sim = 1;
		pthread_mutex_unlock(&(*philos)[0].data->end_sim_lock);
		pthread_mutex_lock(&(*philos)[0].data->start_lock);
		(*philos)[0].data->start_sim = 1;
		pthread_mutex_unlock(&(*philos)[0].data->start_lock);
		while (i < err)
		{
			pthread_join((*philos)[i].thread, NULL);
			i++;
		}
	}
	return (1);
}

/*
 * f_num = number of forks created
 * p_num = number of philos created
 *
 * Destroy mutex for forks and philos and free their array.
 */
void	cleanup(t_data *data, t_philo **philos, int f_num, int p_num)
{
	int	i;

	if (f_num)
	{
		pthread_mutex_destroy(&data->end_sim_lock);
		pthread_mutex_destroy(&data->start_lock);
		i = 0;
		while (i < f_num)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (p_num)
	{
		i = 0;
		while (i < p_num)
		{
			pthread_mutex_destroy(&(*philos)[i].eaten_lock);
			pthread_mutex_destroy(&(*philos)[i].last_eat_lock);
			i++;
		}
		free(*philos);
	}
}
