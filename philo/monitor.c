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

int	verify_fullfiled(t_table *table)
{
	int	i;

	i = 0;
	if (table->max_eat == -1)
		return (0);
	pthread_mutex_lock(&table->ph_num_phs);
	if (table->num_full == table->num_phs)
	{
		pthread_mutex_unlock(&table->ph_num_phs);
		table->is_full = 1;
		return (1);
	}
	pthread_mutex_unlock(&table->ph_num_phs);
	i++;
	return (0);
}

int	verify_death(t_table *table)
{
	int		i;
	size_t	time;

	i = 0;
	while (i < table->num_phs && !is_someone_dead(table, 0))
	{
		pthread_mutex_lock(&table->philos[i].ph_meal);
		time = (size_t)(get_time() - table->philos[i].lst_meal);
		pthread_mutex_unlock(&table->philos[i].ph_meal);
		if (!is_fullfiled(&table->philos[i]) && time > table->t_to_die)
		{
			pthread_mutex_lock(&table->philos[i].ph_dead);
			table->is_dead = table->philos[i].id + 1;
			pthread_mutex_unlock(&table->philos[i].ph_dead);
			print_dead(table);
			return (1);
		}
		if (verify_fullfiled(table))
			return (1);
		i++;
	}
	return (0);
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
	while (1)
	{
		if (verify_fullfiled(table) || verify_death(table))
			break ;
	}
	pthread_mutex_lock(&table->ph_end_din);
	table->end_din = 1;
	pthread_mutex_unlock(&table->ph_end_din);
	return (NULL);
}
