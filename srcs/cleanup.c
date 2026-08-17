/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:55:31 by timtan            #+#    #+#             */
/*   Updated: 2026/08/17 12:53:10 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Destroy the mutexes
 * Free the memory of philos
 * Free the memory of forks
 */
void	cleanup(t_data *data, t_philo **philos, int f_created, int p_created)
{
	int	i;

	if (f_created)
	{
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
			pthread_mutex_destroy(&(*philos)[i].is_dead_lock);
			pthread_mutex_destroy(&(*philos)[i].eaten_lock);
			i++;
		}
		free(*philos);
	}
}
