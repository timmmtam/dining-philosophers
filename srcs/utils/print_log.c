/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 18:25:50 by timtan            #+#    #+#             */
/*   Updated: 2026/08/22 17:45:27 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->end_sim_lock);
	if (philo->data->end_sim == 1)
	{
		pthread_mutex_unlock(&philo->data->end_sim_lock);
		return ;
	}
	printf("%lldms %zu %s\n", current_time_in_ms(), philo->position, message);
	pthread_mutex_unlock(&philo->data->end_sim_lock);
}
