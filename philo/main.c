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

int		take_forks(t_philo *philo)
{
	int	result;

	if (philo->id_philo % 2)
	{
		result = (pthread_mutex_lock(philo->left_fork)
				&& pthread_mutex_lock(philo->right_fork));
	}
	else
	{
		result = (pthread_mutex_lock(philo->right_fork)
				&& pthread_mutex_lock(philo->left_fork));
	}
	return (result);
}

int	release_forks(t_philo *philo)
{
	int	result;

	if (philo->id_philo % 2)
	{
		result = (pthread_mutex_unlock(philo->left_fork)
				&& pthread_mutex_unlock(philo->right_fork));
	}
	else
	{
		result = (pthread_mutex_unlock(philo->right_fork)
				&& pthread_mutex_unlock(philo->left_fork));
	}
	return (result);
}

int		eating(t_philo *philo)
{
	take_forks(philo);
	printf("Philo %d está comendo\n", philo->id_philo);
	usleep(200 * 1000);
	release_forks(philo);
	return (EXIT_SUCCESS);
}

void	*routine(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	eating(&philo);
	return(NULL);
}

int	ft_print_error(char *error)
{
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
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
// Criar função para setar garfos aos filosofos
// Criar função de inicializar os threads
// Criar função de inizialiar os mutexes
// Criar função de inicializar valores
// Criar função de conversão de milisegundos para microsegundos
//

int	init_table(t_table *table, int argc, char **argv)
{
	table->num_of_philos = ft_atol(argv[1]);
	// table->t_to_die;
	// table->t_to_eat;
	// table->t_to_sleep;
	// table->max_eat;
	(void)argc;
	return (0);
}

int	main(int argc, char **argv)
{
	t_table			table;
	t_philo			philos[2];
	pthread_mutex_t	mut_t1;
	pthread_mutex_t	mut_t2;
	long			initial_time;

	if (argc < 5 || argc > 6)
		return(ft_print_error("Invalid amount of parameters. \nUse this command: \n"
				"./philo number_of_philos time_to_die time_to_eat "
				"time_to_sleep [number_of_times_each_philosopher_must_eat]"));
	if (is_invalid_param(argv))
		return (EXIT_FAILURE);
	(void)argv;
	(void)table;
	initial_time = get_time();
	printf("Initial time: %ld\n", initial_time - initial_time);
	philos[0].id_philo = 0;
	philos[1].id_philo = 1;
	philos[0].philo = &table.ph_th[0];
	philos[1].philo = &table.ph_th[1];
	pthread_mutex_init(&mut_t1, NULL);
	pthread_mutex_init(&mut_t2, NULL);
	philos[0].left_fork = &mut_t1;
	philos[0].right_fork = &mut_t2;
	philos[1].left_fork = &mut_t2;
	philos[1].right_fork = &mut_t1;
	pthread_create(philos[0].philo, NULL, &routine, &(philos[0]));
	pthread_create(philos[1].philo, NULL, &routine, &(philos[1]));
	pthread_join(*philos[0].philo, NULL);
	pthread_join(*philos[1].philo, NULL);
	pthread_mutex_destroy(&mut_t1);
	pthread_mutex_destroy(&mut_t2);
	printf("Initial time: %ld\n", get_time() - initial_time);
	return (EXIT_SUCCESS);
}