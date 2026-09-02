/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:55:31 by timtan            #+#    #+#             */
/*   Updated: 2026/09/02 18:15:58 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * f_created = flag if forks are created (also the number of philo/forks)
 * p_created = flag if philo array is created
 *
 * Destroy mutex for forks and philos and free their array.
 */
void	cleanup(t_data *data, t_philo **philos, int f_created, int p_created)
{
	int	i;

	if (f_created)
	{
		pthread_mutex_destroy(&data->end_sim_lock);
		i = 0;
		while (i < f_created)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (p_created)
	{
		i = 0;
		while (i < p_created)
		{
			pthread_mutex_destroy(&(*philos)[i].eaten_lock);
			pthread_mutex_destroy(&(*philos)[i].last_eat_lock);
			i++;
		}
		free(*philos);
	}
}
