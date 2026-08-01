/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:44:23 by timtan            #+#    #+#             */
/*   Updated: 2026/04/21 16:07:04 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("Failed\n"), -1);
	else
		return (((long long)tv.tv_sec * 1000) + ((long long)tv.tv_usec / 1000));
}

void	msleep(int ms)
{
	long long	start_time;

	start_time = current_time_in_ms();
	while (current_time_in_ms() - start_time < ms)
		usleep(500);
}

/*int	main(void)
{
	long long	start_time;
	long long	end_time;

	start_time = current_time_in_ms();
	msleep(100005);
	end_time = current_time_in_ms();
	printf("Start Time: %lld\n", start_time);
	printf("End Time: %lld\n", end_time);
	printf("Elapsed Time: %lld\n", end_time - start_time);
	return(0);
}*/
