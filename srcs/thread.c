/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:42:48 by timtan            #+#    #+#             */
/*   Updated: 2026/09/02 18:06:02 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		return (printf("Thread creation failed for waitress.\n"), 1);
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_create(&(*philos)[i].thread, NULL, philo_routine, &(*philos)[i]) != 0)
			return (printf("Thread creation failed for philo.\n"), 1);
		i++;
	}
	i = 0;
	if (pthread_join(waitress, NULL) != 0)
		return (printf("Thread joining failed for waitress.\n"), 2);
	while (i < data->num_of_philo)
	{
		if (pthread_join((*philos)[i].thread, NULL) != 0)
			return (printf("Thread joining failed for philo.\n"), 2);
		i++;
	}
	return (0);
}
