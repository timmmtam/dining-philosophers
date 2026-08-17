/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 12:37:43 by timtan            #+#    #+#             */
/*   Updated: 2026/08/17 10:37:13 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	* Checks if meals eaten satisfies the number of times to eat.
	* Relies on dead_check to end the routine loop by setting dead = 1.
	* Returns 0 if num_of_eat is not specified of philos are not satisfied.
	* Returns 1 if all philos are satisfied.
 */
static int	eaten_check(t_philo **philos)
{
	size_t	i;
	size_t	num_of_philo;
	size_t	ate_finish;
	t_philo	*philo;

	if ((*philos)[0].num_of_eat < 1)
		return (0);
	i = 0;
	ate_finish = 0;
	num_of_philo = (*philos)[0].num_of_philo;
	while (i < num_of_philo)
	{
		philo = &(*philos)[i];
		pthread_mutex_lock(&philo->eaten_lock);
		if (philo->times_eaten == philo->num_of_eat)
			ate_finish += 1;
		pthread_mutex_unlock(&philo->eaten_lock);
		i++;
	}
	if (ate_finish == num_of_philo)
		return (1);
	return(0);
}

/*
	* Checks if each philo is starved or satisfied.
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
	num_of_philo = (*philos)[0].num_of_philo;
	while (i < num_of_philo)
	{
		philo = &(*philos)[i];
		if ((current_time_in_ms() - philo->last_eaten > philo->ttd))
		{
			pthread_mutex_lock(&philo->is_dead_lock);
			philo->dead = 1;
			pthread_mutex_unlock(&philo->is_dead_lock);
			print_log(philo, "died");
			is_dead = 1;
			break;
		}
		i++;
	}
	return (is_dead);
}

static void	stop_routine(t_philo **philos)
{
	size_t	i;
	size_t	num_of_philo;
	t_philo	*philo;

	i = 0;
	num_of_philo = (*philos)[0].num_of_philo;
	while (i < num_of_philo)
	{
		philo = &(*philos)[i];
		pthread_mutex_lock(&philo->is_dead_lock);
		philo->dead = 1;
		pthread_mutex_unlock(&philo->is_dead_lock);
		i++;
	}
}

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
}
