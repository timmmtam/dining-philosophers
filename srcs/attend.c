/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 12:37:43 by timtan            #+#    #+#             */
/*   Updated: 2026/08/29 16:48:51 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	end_sim(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_sim_lock);
	philo->data->end_sim = 1;
	pthread_mutex_unlock(&philo->data->end_sim_lock);
	return (1);
}

/*
	* Role: Checks if meals eaten satisfies the number of times to eat.
	* Returns 0 if philo has not finished eating.
	* Returns 1 if philo has finished eating.
 */
static int	ate_check(t_philo *philo)
{
	int	ate;

	ate = 0;
	pthread_mutex_lock(&philo->eaten_lock);
	if (philo->times_eaten == philo->data->num_of_eat)
		ate = 1;
	pthread_mutex_unlock(&philo->eaten_lock);
	return(ate);
}

/*
	* Role: To check if philo is starved.
	* Returns 1 if philo is dead.
	* Returns 0 if philo is alive.
	* end_sim() is called here to avoid messages printing after philo dies.
*/
static int	dead_check(t_philo *philo)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&philo->last_eat_lock);
	if ((current_time_in_ms() - philo->last_eaten > philo->data->ttd))
	{
		pthread_mutex_unlock(&philo->last_eat_lock);
		print_log(philo, "died");
		end_sim(philo);
		dead = 1;
	}
	else
		pthread_mutex_unlock(&philo->last_eat_lock);
	return (dead);
}

/*
 * The routine passed into the waiter thread with the array of philos as arg.
 * Role: To check if any philo has died or if philos have finished eating.
 * If either condition is satisfied, end_sim() is called to end simulation.
 */
void	*attend(void *arg)
{
	t_philo	**philos;
	int		end;
	size_t	ate_finish;
	size_t	i;

	philos = (t_philo**)arg;
	end = 0;
	ate_finish = 0;
	i = 0;
	while (!end)
	{
		while (i < (*philos)[0].data->num_of_philo)
		{
			if ((end = dead_check(&(*philos)[i])))
				break;
			if ((*philos)[0].data->num_of_eat > 0)
				ate_finish += ate_check(&(*philos)[i]);
			i++;
		}
		if (ate_finish == (*philos)[0].data->num_of_philo)
			end = end_sim(&(*philos)[0]);
	}
	return (NULL);
}
