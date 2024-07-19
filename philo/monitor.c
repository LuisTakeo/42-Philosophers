/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:09:30 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/07/16 22:09:30 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_dead(t_table *table)
{
	pthread_mutex_lock(&table->ph_is_d);
	pthread_mutex_lock(&table->ph_print);
	printf("%ld %d is dead\n", (size_t)((get_time()) - table->init_time),
		table->is_dead);
	pthread_mutex_unlock(&table->ph_print);
	pthread_mutex_unlock(&table->ph_is_d);
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

int	verify_death(t_table *table)
{
	int		i;
	int		is_dead;

	i = 0;
	while (i < table->num_phs)
	{
		pthread_mutex_lock(&table->ph_num_phs);
		if (table->num_full == table->num_phs)
		{
			pthread_mutex_unlock(&table->ph_num_phs);
			return (1);
		}
		pthread_mutex_unlock(&table->ph_num_phs);
		if (is_someone_dead(table, 0))
		{
			print_dead(table);
			return (1);
		}
		i++;
		;
	}
	pthread_mutex_lock(&table->ph_is_d);
	is_dead = table->is_dead;
	pthread_mutex_unlock(&table->ph_is_d);
	return (is_dead);
}

void	*monitoring(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		pthread_mutex_lock(&table->ph_num_phs_init);
		if (table->num_phs == table->num_phs_init)
		{
			pthread_mutex_unlock(&table->ph_num_phs_init);
			break ;
		}
		pthread_mutex_unlock(&table->ph_num_phs_init);
	}
	pthread_mutex_lock(&table->ph_init);
	table->is_created = 1;
	pthread_mutex_unlock(&table->ph_init);
	while (!verify_death(table))
		usleep(1000);
	pthread_mutex_lock(&table->ph_end_din);
	table->end_din = 1;
	pthread_mutex_unlock(&table->ph_end_din);
	return (NULL);
}
