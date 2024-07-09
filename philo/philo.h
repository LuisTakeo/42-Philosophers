/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:03:35 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/06/27 16:03:35 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

struct s_philo
{
	pthread_t		*philo;
	int				id_philo;
	int				eat_times;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
};

struct s_table
{
	pthread_t	philos[200];
	pthread_t	monitor;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			max_eating;
	int			number_of_philos;
};

int		ft_issignal(char c);
int		ft_isspace(char c);
int		ft_strlen(char *str);
int		ft_isdigit(int c);
int		is_int(char *arg);
long	ft_atol(const char *nptr);

#endif