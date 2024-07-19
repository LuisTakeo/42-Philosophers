/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_dead.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 07:47:23 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/07/12 07:47:23 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	update_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->ph_is_d);
	philo->table->is_dead = 1 + philo->id;
	pthread_mutex_unlock(&philo->table->ph_is_d);
	return (1);
}

int	is_someone_dead(t_table *table, int is_philo)
{
	if (is_philo)
		usleep(0);
	pthread_mutex_lock(&table->ph_is_d);
	if (table->is_dead)
	{
		pthread_mutex_unlock(&table->ph_is_d);
		return (1);
	}
	pthread_mutex_unlock(&table->ph_is_d);
	return (0);
}
