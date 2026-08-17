/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 16:54:03 by timtan            #+#    #+#             */
/*   Updated: 2026/08/17 10:46:44 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philo *philo)
{
	print_log(philo, "is thinking");
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	print_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo->left_fork);
	print_log(philo, "has taken a fork");
	philo->eating = 1;
	print_log(philo, "is eating");
	msleep(philo->tte);
	philo->last_eaten = current_time_in_ms();
	philo->eating = 0;
	pthread_mutex_lock(&philo->eaten_lock);
	philo->times_eaten += 1;
	pthread_mutex_unlock(&philo->eaten_lock);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

static void	philo_sleep(t_philo *philo)
{
	print_log(philo, "is sleeping");
	msleep(philo->tts);
}

static int	is_dead(t_philo *philo)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&philo->is_dead_lock);
	if (philo->dead == 1)
		dead = 1;
	pthread_mutex_unlock(&philo->is_dead_lock);
	return (dead);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_dead(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
