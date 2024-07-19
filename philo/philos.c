/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:12:06 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/07/19 15:12:06 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_philos(t_table *table)
{
	int	i;

	i = 0;
	if (table->num_phs > 1)
		if (pthread_join(table->mon, NULL) != 0)
			return (ft_print_error("Error joining thread"));
	while (i < table->num_phs)
	{
		if (pthread_join(*(table->philos[i].philo), NULL) != 0)
			return (ft_print_error("Error joining thread"));
		i++;
	}
	return (0);
}

int	create_philos(t_table *table)
{
	int	i;

	i = 0;
	table->init_time = get_time();
	if (table->num_phs == 1)
	{
		if (pthread_create(table->philos[0].philo, NULL,
				&single_routine, &(table->philos[0])) != 0)
			return (ft_print_error("Error creating thread"));
	}
	else
	{
		if (pthread_create(&(table->mon), NULL, &monitoring, table) != 0)
			return (ft_print_error("Error creating thread"));
		while (i < table->num_phs)
		{
			if (pthread_create(table->philos[i].philo, NULL,
					&routine, &(table->philos[i])) != 0)
				return (ft_print_error("Error creating thread"));
			i++;
		}
	}
	if (join_philos(table))
		return (EXIT_FAILURE);
	return (0);
}
