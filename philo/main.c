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

int	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->ph_print);
	printf(msg, (int)(get_time() - philo->table->init_time),
		philo->id_philo + 1);
	pthread_mutex_unlock(&philo->table->ph_print);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	philo;
	int		i;

	philo = *(t_philo *)arg;
	i = 0;
	while (i < 10)
	{
		eating(&philo);
		sleeping(&philo);
		thinking(&philo);
		i++;
	}
	// sleeping
	// thinking
	return (NULL);
}

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

// Validação de argumentos -> DONE!
// Criar função para setar garfos aos filosofos -> DONE
// Criar função de inicializar os threads
// Criar função de inizialiar os mutexes -> DONE
// Criar função de inicializar valores -> DONE
// Criar função de conversão de milisegundos para microsegundos -> DONE
// Criar mutexes para manipulação de variáveis compartilhadas
// Criar função que capturará quando um philo morreu

int	finish_dinner(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		pthread_mutex_destroy(&table->ph_mutex[i++]);
		free(table->philos);
	}
	pthread_mutex_destroy(&table->ph_print);
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
	printf("Initial time: %ld\n", table.init_time - table.init_time);
	pthread_create(table.philos[0].philo, NULL, &routine, &(table.philos[0]));
	pthread_create(table.philos[1].philo, NULL, &routine, &(table.philos[1]));
	pthread_join(*(table.philos[0].philo), NULL);
	pthread_join(*(table.philos[1].philo), NULL);
	printf("Finish time: %ld\n", get_time() - table.init_time);
	finish_dinner(&table);
	return (EXIT_SUCCESS);
}