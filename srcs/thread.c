/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:42:48 by timtan            #+#    #+#             */
/*   Updated: 2026/09/07 08:25:39 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_sim(t_data *data)
{
	pthread_mutex_lock(&data->start_lock);
	data->start_time = current_time_in_ms();
	data->start_sim = 1;
	pthread_mutex_unlock(&data->start_lock);
}

/*
	* Starts each philo thread, passing the philo routine as a function.
	* Returns 1 if malloc failed, 2 if pthread_create failed, -
	* 3 if pthread_join failed and 0 upon successful execution.
*/
int	start_threads(t_data *data, t_philo **philos)
{
	pthread_t	waitress;
	size_t			i;

	if (pthread_create(&waitress, NULL, attend, philos))
		return (thread_cleanup(philos, -1));
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_create(&(*philos)[i].thread, NULL, philo_routine, &(*philos)[i]) != 0)
			return (thread_cleanup(philos, i));
		i++;
	}
	start_sim(data);
	i = 0;
	pthread_join(waitress, NULL);
	while (i < data->num_of_philo)
	{
		pthread_join((*philos)[i].thread, NULL);
		i++;
	}
	return (0);
}
