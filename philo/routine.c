/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:03:14 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/06/27 16:03:14 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_routine(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	pthread_mutex_lock(philo.l_fork);
	print_action(&philo, "%d %d has taken a fork\n");
	usleep(philo.table->t_to_die * 1000);
	pthread_mutex_unlock(philo.l_fork);
	print_action(&philo, "%d %d is dead\n");
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->table->ph_num_phs_init);
    philo->table->num_phs_init++;
    pthread_mutex_unlock(&philo->table->ph_num_phs_init);
    while (!is_created(philo->table))
    {
        philo->lst_meal = philo->table->init_time;
    }
	// if (philo->id % 2 == 0)
	// 	usleep(100);
	while (!is_someone_dead(philo->table, 1) && !is_fullfiled(philo))
	{
		eating(philo);
		if (is_someone_dead(philo->table, 1) || is_fullfiled(philo))
			break ;
		sleep_n_think(philo);
	}
	while (!is_end_dinner(philo->table))
		;
	return (NULL);
}

int		is_created(t_table *table)
{
	pthread_mutex_lock(&table->ph_init);
	if (table->is_created)
	{
		pthread_mutex_unlock(&table->ph_init);
		return (1);
	}
	pthread_mutex_unlock(&table->ph_init);
	return (0);
}

void	print_action(t_philo *philo, char *msg)
{
	if (is_someone_dead(philo->table, 1) || is_fullfiled(philo))
		return ;
	pthread_mutex_lock(&philo->table->ph_print);
	printf(msg, (size_t)((get_time()) - philo->table->init_time),
	philo->id + 1);
	pthread_mutex_unlock(&philo->table->ph_print);
}

int	is_fullfiled(t_philo *philo)
{
	if (philo->table->max_eat == -1)
		return (0);
	pthread_mutex_lock(&philo->table->ph_is_full);
	if (philo->eat_t >= philo->table->max_eat)
	{
		pthread_mutex_unlock(&philo->table->ph_is_full);
		pthread_mutex_lock(&philo->table->ph_num_phs);
		philo->table->num_full++;
		pthread_mutex_unlock(&philo->table->ph_num_phs);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->ph_is_full);
	return (0);
}
