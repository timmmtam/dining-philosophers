/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 18:25:50 by timtan            #+#    #+#             */
/*   Updated: 2026/08/16 09:48:11 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->print_lock);
	printf("%lldms %d %s\n", current_time_in_ms(), philo->position, message);
	pthread_mutex_unlock(&philo->print_lock);
}
