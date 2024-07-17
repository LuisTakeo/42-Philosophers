/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:09:30 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/07/16 22:09:30 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_someone_dead(t_table *table)
{
	pthread_mutex_lock(&table->ph_is_dead);
	if (table->is_dead)
	{
		pthread_mutex_unlock(&table->ph_is_dead);
		return (1);
	}
	pthread_mutex_unlock(&table->ph_is_dead);
	return (0);
}

int	verify_death(t_table *table)
{
	int		i;
	int		is_dead;
	long	last;

	i = 0;
	while (i < table->num_of_philos && !is_someone_dead(table))
	{
		pthread_mutex_lock(&table->ph_lst_meal);
		last = table->philos[i].last_meal;

		if ((get_time() - table->philos[i].last_meal) >= table->t_to_die)
		{
			pthread_mutex_lock(&table->ph_is_dead);
			table->is_dead = 1;
			pthread_mutex_unlock(&table->ph_is_dead);
			print_action(&table->philos[i], "%d %d is dead\n", 0);
		}
		pthread_mutex_unlock(&table->ph_lst_meal);
		i++;
	}
	pthread_mutex_lock(&table->ph_is_dead);
	is_dead = table->is_dead;
	pthread_mutex_unlock(&table->ph_is_dead);
	return (is_dead);
}

void	*monitoring(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!verify_death(table))
		usleep(50);
	return (NULL);
}
