/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:03:14 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/06/27 16:03:14 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_invalid_param(char **argv)
{
	char	**temp;
	long	value;

	value = 0;
	temp = (argv + 1);
	while (*temp)
	{
		if (is_int(*temp))
			return (ft_print_error("Wrong parameter. "
					"Use positive numbers in int scope"));
		value = ft_atol(*temp);
		if (value < 0 || value > INT_MAX)
			return (ft_print_error("Wrong parameter. "
					"Use only positive numbers in int scope"));
		temp++;
	}
	return (EXIT_SUCCESS);
}

int	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_phs)
	{
		pthread_mutex_destroy(&table->philos[i].ph_meal);
		pthread_mutex_destroy(&table->philos[i].ph_dead);
		pthread_mutex_destroy(&table->ph_mut[i++]);
	}
	pthread_mutex_destroy(&table->ph_print);
	pthread_mutex_destroy(&table->ph_is_d);
	pthread_mutex_destroy(&table->ph_lst_ml);
	pthread_mutex_destroy(&table->ph_is_full);
	pthread_mutex_destroy(&table->ph_end_din);
	pthread_mutex_destroy(&table->ph_init);
	pthread_mutex_destroy(&table->ph_num_phs);
	pthread_mutex_destroy(&table->ph_num_phs_init);
	return (0);
}

int	finish_dinner(t_table *table)
{
	destroy_mutexes(table);
	if (table->ph_mut)
	{
		free(table->ph_mut);
		table->ph_mut = NULL;
	}
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table			table;

	if (argc < 5 || argc > 6)
		return (ft_print_error("Invalid amount of parameters. \n"
				"Use this command:\n"
				"./philo number_of_philos time_to_die time_to_eat "
				"time_to_sleep [number_of_times_each_philosopher_must_eat]"));
	if (is_invalid_param(argv) || init_table(&table, argc, argv))
		return (EXIT_FAILURE);
	if (table.max_eat == 0)
		return (EXIT_SUCCESS);
	if (create_philos(&table))
		return (EXIT_FAILURE);
	finish_dinner(&table);
	return (EXIT_SUCCESS);
}
