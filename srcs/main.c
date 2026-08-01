/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:16:57 by timtan            #+#    #+#             */
/*   Updated: 2026/07/18 13:20:04 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	* Philos is a pointer pointing to multiple philo instances.
	* Hence, the plurality.
*/
int	main(int ac, char **av)
{
	t_philo	*philos;
	t_data	data;

	if (ac < 5 || ac > 6)
		return (printf("Invalid Parameters.\n"), 1);
	data = (t_data){0};
	if (init_program(&data, &philos, ac, av))
		return (1);
	if (start_threads(&data, &philos))
		//add cleanup or error message here.
	cleanup(&data, &philos, data.num_of_philo, 1);
	return (0);
}
