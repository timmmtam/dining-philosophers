/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 18:25:50 by timtan            #+#    #+#             */
/*   Updated: 2026/08/17 12:52:16 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lldms %zu %s\n", current_time_in_ms(), philo->position, message);
	pthread_mutex_unlock(&philo->data->print_lock);
}
