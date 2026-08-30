/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 18:25:50 by timtan            #+#    #+#             */
/*   Updated: 2026/08/30 17:55:05 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_philo *philo, char *message)
{
	long long	elapsed_time;

	pthread_mutex_lock(&philo->data->end_sim_lock);
	if (philo->data->end_sim == 1)
	{
		pthread_mutex_unlock(&philo->data->end_sim_lock);
		return ;
	}
	elapsed_time = current_time_in_ms() - philo->data->start_time;
	printf("%lld %zu %s\n", elapsed_time, philo->position + 1, message);
	pthread_mutex_unlock(&philo->data->end_sim_lock);
}
