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
	if (philo->id % 2)
	{
		usleep(40);
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "%d %d has taken a fork\n", 1);
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "%d %d has taken a fork\n", 1);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "%d %d has taken a fork\n", 1);
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "%d %d has taken a fork\n", 1);
	}
	return (0);
}

int	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		usleep(40);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	return (0);
}

int	is_end_dinner(t_table *table)
{
	pthread_mutex_lock(&table->ph_end_din);
	if (table->end_din)
	{
		pthread_mutex_unlock(&table->ph_end_din);
		return (1);
	}
	pthread_mutex_unlock(&table->ph_end_din);
	return (0);
}

int	eating(t_philo *philo)
{
	take_forks(philo);
	if (is_someone_dead(philo->table))
		return (release_forks(philo));
	print_action(philo, "%d %d is eating\n", 1);
	pthread_mutex_lock(&philo->table->ph_lst_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->ph_lst_meal);
	philo->eat_times += 1;
	usleep(philo->table->t_to_eat * 1000);
	release_forks(philo);
	return (EXIT_SUCCESS);
}

int	sleeping(t_philo *philo)
{
	print_action(philo, "%d %d is sleeping\n", 1);
	usleep(philo->table->t_to_sleep * 1000);
	return (EXIT_SUCCESS);
}

int	thinking(t_philo *philo)
{
	print_action(philo, "%d %d is thinking\n", 1);
	return (EXIT_SUCCESS);
}
