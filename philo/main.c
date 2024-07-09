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

int		eating(t_philo *philo)
{
	if (philo->id_philo % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	printf("Philo %d está comendo\n", philo->id_philo);
	usleep(1000000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t		philos_threads[2];
	t_philo			philos[2];
	pthread_mutex_t	mut_t1;
	pthread_mutex_t	mut_t2;

	if (argc < 5 || argc > 6)
		return(ft_print_error("Invalid amount of parameters. \nUse this command: \n"
				"./philo number_of_philos time_to_die time_to_eat "
				"time_to_sleep [number_of_times_each_philosopher_must_eat]"));
	if (is_invalid_param(argv))
		return (EXIT_FAILURE);
	(void)argv;
	(void)table;
	philos[0].id_philo = 0;
	philos[1].id_philo = 1;
	philos[0].philo = &philos_threads[0];
	philos[1].philo = &philos_threads[1];
	pthread_mutex_init(&mut_t1, NULL);
	pthread_mutex_init(&mut_t2, NULL);
	philos[0].left_fork = &mut_t1;
	philos[0].right_fork = &mut_t2;
	philos[1].left_fork = &mut_t2;
	philos[1].right_fork = &mut_t1;
	pthread_create(philos[0].philo, NULL, &routine, &(philos[0]));
	pthread_create(philos[1].philo, NULL, &routine, &(philos[1]));
	pthread_join(*philos[0].philo, NULL);
	usleep(200);
	pthread_join(*philos[1].philo, NULL);
	pthread_mutex_destroy(&mut_t1);
	pthread_mutex_destroy(&mut_t2);
	return (EXIT_SUCCESS);
}