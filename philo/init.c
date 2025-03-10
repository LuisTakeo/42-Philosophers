/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 07:30:09 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/07/12 07:30:09 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table, int argc, char **argv)
{
	table->num_phs = ft_atol(argv[1]);
	table->t_to_die = ft_atol(argv[2]);
	table->t_to_eat = ft_atol(argv[3]);
	table->t_to_sleep = ft_atol(argv[4]);
	table->max_eat = -1;
	table->is_dead = 0;
	table->end_din = 0;
	table->is_created = 0;
	table->num_full = 0;
	table->num_phs_init = 0;
	table->is_full = 0;
	if (argc == 6)
		table->max_eat = ft_atol(argv[5]);
	if (table->max_eat == 0)
		return (0);
	if (table->num_phs > 200 || table->num_phs < 1)
		return (ft_print_error("Invalid number of "
				"philosophers. Min value: 1, Max value: 200"));
	if (init_struct_philos(table))
		return (1);
	return (0);
}

int	init_struct_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * (table->num_phs));
	if (!table->philos)
		return (1);
	i = 0;
	init_mutexes(table);
	while (i < table->num_phs)
	{
		table->philos[i].philo = &table->ph_th[i];
		table->philos[i].id = i;
		table->philos[i].eat_t = 0;
		table->philos[i].lst_meal = get_time();
		table->philos[i].l_fork = &table->ph_mut[i];
		table->philos[i].r_fork = NULL;
		if (table->num_phs > 1)
			table->philos[i].r_fork = &table->ph_mut[(i + 1)
				% table->num_phs];
		table->philos[i].table = table;
		i++;
	}
	return (0);
}

int	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	table->ph_mut = malloc(sizeof(pthread_mutex_t) * table->num_phs);
	if (!table->ph_mut)
		return (1);
	pthread_mutex_init(&table->ph_print, NULL);
	pthread_mutex_init(&table->ph_is_d, NULL);
	pthread_mutex_init(&table->ph_lst_ml, NULL);
	pthread_mutex_init(&table->ph_is_full, NULL);
	pthread_mutex_init(&table->ph_end_din, NULL);
	pthread_mutex_init(&table->ph_init, NULL);
	pthread_mutex_init(&table->ph_num_phs, NULL);
	pthread_mutex_init(&table->ph_num_phs_init, NULL);
	while (i < table->num_phs)
	{
		pthread_mutex_init(&table->philos[i].ph_dead, NULL);
		pthread_mutex_init(&table->philos[i].ph_meal, NULL);
		pthread_mutex_init(&table->ph_mut[i], NULL);
		i++;
	}
	return (0);
}
