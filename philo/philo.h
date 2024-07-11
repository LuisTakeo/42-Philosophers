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
typedef struct timeval	t_timeval;


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
	pthread_t		ph_th[200];
	pthread_t		monitor;
	pthread_mutex_t	ph_mutex[200];
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	int				max_eat;
	int				num_of_philos;
};

int		ft_issignal(char c);
int		ft_isspace(char c);
int		ft_strlen(char *str);
int		ft_isdigit(int c);
int		is_int(char *arg);
long	ft_atol(const char *nptr);
long	get_time(void);

#endif