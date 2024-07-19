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
	if (philo->id % 2 == 0)
	{
		// usleep(40);
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "%d %d has taken a fork\n");
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "%d %d has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "%d %d has taken a fork\n");
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "%d %d has taken a fork\n");
	}
	return (0);
}

int	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
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

int	update_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->ph_is_d);
	philo->table->is_dead = 1 + philo->id;
	pthread_mutex_unlock(&philo->table->ph_is_d);
	return (1);
}

int	eating(t_philo *philo)
{
	size_t	time;

	take_forks(philo);
	if (is_someone_dead(philo->table, 1) || is_fullfiled(philo))
		return (release_forks(philo));

	time = get_time();
	if ((size_t)(time - philo->lst_meal) > philo->table->t_to_die)
	{
		update_dead(philo);
	}
	// pthread_mutex_unlock(&philo->table->ph_lst_ml);
	philo->lst_meal = time;
	print_action(philo, "%d %d is eating\n");
	philo->eat_t += 1;
	release_forks(philo);
	usleep(philo->table->t_to_eat * 1000);
	return (EXIT_SUCCESS);
}

int	sleep_n_think(t_philo *philo)
{
	print_action(philo, "%d %d is sleeping\n");
	usleep(philo->table->t_to_sleep * 1000);
	if (is_someone_dead(philo->table, 1) || is_fullfiled(philo))
		return (EXIT_SUCCESS);
	print_action(philo, "%d %d is thinking\n");
	usleep(0);
	return (EXIT_SUCCESS);
}
