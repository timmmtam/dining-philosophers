/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 12:37:43 by timtan            #+#    #+#             */
/*   Updated: 2026/08/22 15:48:49 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_sim(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_sim_lock);
	philo->data->end_sim = 1;
	pthread_mutex_unlock(&philo->data->end_sim_lock);
}

/*
	* Checks if meals eaten satisfies the number of times to eat.
	* Returns 0 if num_of_eat is not specified of philos are not satisfied.
	* Returns 1 if all philos are satisfied.
 */
static int	eaten_check(t_philo **philos)
{
	size_t	i;
	size_t	num_of_philo;
	size_t	ate_finish;
	t_philo	*philo;

	if ((*philos)[0].data->num_of_eat < 1)
		return (0);
	i = 0;
	ate_finish = 0;
	num_of_philo = (*philos)[0].data->num_of_philo;
	while (i < num_of_philo)
	{
		philo = &(*philos)[i];
		pthread_mutex_lock(&philo->eaten_lock);
		if (philo->times_eaten == philo->data->num_of_eat)
			ate_finish += 1;
		pthread_mutex_unlock(&philo->eaten_lock);
		i++;
	}
	if (ate_finish == num_of_philo)
	{
		end_sim(&(*philos)[0]);
		return (1);
	}
	return(0);
}

/*
	* Role: To check if each philo is starved.
	* Sets dead = 1 if yes. To end the routine and stop program.
*/
static int	dead_check(t_philo **philos)
{
	size_t	i;
	size_t	num_of_philo;
	t_philo	*philo;
	int		is_dead;

	i = 0;
	is_dead = 0;
	num_of_philo = (*philos)[0].data->num_of_philo;
	while (i < num_of_philo)
	{
		philo = &(*philos)[i];
		if ((current_time_in_ms() - philo->last_eaten > philo->data->ttd))
		{
			end_sim(philo);
			print_log(philo, "died");
			is_dead = 1;
			break;
		}
		i++;
	}
	return (is_dead);
}

/*
 * The routine passed into the waiter thread with the array of philos as arg.
 * Role: To call dead_check and eaten_check until one of then is satisfied.
 */
void	*attend(void *arg)
{
	t_philo	**philos;
	int		end;

	philos = (t_philo**)arg;
	end = 0;
	while (!end)
	{
		if (dead_check(philos) || eaten_check(philos))
			end = 1;
	}
	stop_routine(philos);
	return (NULL);
}
