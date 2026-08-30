/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:37:50 by timtan            #+#    #+#             */
/*   Updated: 2026/08/30 14:33:59 by timtan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Converts string to size_t.
 * Handles overflow and trailing non-numbers.
 * Returns 0 on error.
 */
size_t	ft_atoz(const char *nptr)
{
	size_t	i;
	size_t	result;

	i = 0;
	result = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == 32)
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (result > (SIZE_MAX - (nptr[i] - '0')) / 10)
			return (0);
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] != '\0')
		return (0);
	return (result);
}
