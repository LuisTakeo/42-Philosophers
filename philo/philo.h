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
	long			last_meal;
	t_table			*table;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
};

struct s_table
{
	pthread_t		ph_th[200];
	pthread_t		monitor;
	pthread_mutex_t	ph_mutex[200];
	pthread_mutex_t	ph_print;
	pthread_mutex_t	ph_is_dead;
	pthread_mutex_t	ph_lst_meal;
	t_philo			*philos;
	long			init_time;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	int				max_eat;
	int				num_of_philos;
	int				is_dead;
};

// Validators
int		is_invalid_param(char **argv);
// Inits
int		init_table(t_table *table, int argc, char **argv);
int		init_struct_philos(t_table *table);
int		init_mutexes(t_table *table);
int		join_philos(t_table *table);
int		is_created(t_table *table);
// Finishers
int		finish_dinner(t_table *table);
// Actions
int		eating(t_philo *philo);
int		thinking(t_philo *philo);
int		sleeping(t_philo *philo);
int		take_forks(t_philo *philo);
int		release_forks(t_philo *philo);
// Utils
int		ft_issignal(char c);
int		ft_isspace(char c);
int		ft_strlen(char *str);
int		ft_isdigit(int c);
int		is_int(char *arg);
long	ft_atol(const char *nptr);
long	get_time(void);
// Prints
int		print_action(t_philo *philo, char *msg, int is_philo);
int		ft_print_error(char *error);
// Monitoring
void	*monitoring(void *arg);
int		is_someone_dead(t_table *table);
int		verify_death(t_table *table);

#endif