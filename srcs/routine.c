/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 16:54:03 by timtan            #+#    #+#             */
/*   Updated: 2026/09/01 18:20:46 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philo *philo)
{
	print_log(philo, "is thinking");
	if (philo->data->tts <= philo->data->tte)
	{
		if (philo->data->num_of_philo % 2 == 0)
			msleep(philo->data->tte - philo->data->tts + 1);
		else
			msleep((philo->data->tte * 2) - philo->data->tts + 1);
	}
}

static void	philo_eat(t_philo *philo)
{
	if (philo->position % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_log(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_log(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->last_eat_lock);
	philo->last_eaten = current_time_in_ms();
	pthread_mutex_unlock(&philo->last_eat_lock);
	print_log(philo, "is eating");
	msleep(philo->data->tte);
	pthread_mutex_lock(&philo->eaten_lock);
	philo->times_eaten += 1;
	pthread_mutex_unlock(&philo->eaten_lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philo_sleep(t_philo *philo)
{
	print_log(philo, "is sleeping");
	msleep(philo->data->tts);
}

/*
 * Checks if the simulation has ended or if it has finished eating.
 */
static int	is_end(t_philo *philo)
{
	int	end;

	end = 0;
	pthread_mutex_lock(&philo->data->end_sim_lock);
	if (philo->data->end_sim == 1)
		end = 1;
	pthread_mutex_unlock(&philo->data->end_sim_lock);
	if (philo->data->num_of_eat > 0)
	{
		pthread_mutex_lock(&philo->eaten_lock);
		if (philo->times_eaten >= philo->data->num_of_eat)
			end = 1;
		pthread_mutex_unlock(&philo->eaten_lock);
	}
	return (end);
}

/*
 * The routine passed into each thread along with the philo struct as argument
*/
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_of_philo == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_log(philo, "has taken a fork");
		msleep(philo->data->ttd + 5);
		pthread_mutex_unlock(philo->right_fork);
		return (NULL);
	}
	while (!is_end(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
