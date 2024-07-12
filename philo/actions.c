/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 07:47:23 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/07/12 07:47:23 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	if (philo->id_philo % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "%d %d has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "%d %d has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "%d %d has taken a fork\n");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "%d %d has taken a fork\n");
	}
	return (0);
}

int	release_forks(t_philo *philo)
{
	if (philo->id_philo % 2)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (0);
}

int		eating(t_philo *philo)
{
	take_forks(philo);
	philo->last_meal = get_time();
	print_action(philo, "%d %d is eating\n");
	usleep(philo->table->t_to_eat * 1000);

	release_forks(philo);
	return (EXIT_SUCCESS);
}

int		sleeping(t_philo *philo)
{
	print_action(philo, "%d %d is sleeping\n");
	usleep(philo->table->t_to_sleep * 1000);
	return (EXIT_SUCCESS);
}

int		thinking(t_philo *philo)
{
	print_action(philo, "%d %d is thinking\n");
	return (EXIT_SUCCESS);
}