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
	short int		id;
	short int		eat_t;
	long			lst_meal;
	t_table			*table;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
};

struct s_table
{
	pthread_t			ph_th[200];
	pthread_t			mon;
	pthread_mutex_t		*ph_mut;
	pthread_mutex_t		ph_print;
	pthread_mutex_t		ph_is_d;
	pthread_mutex_t		ph_lst_ml;
	pthread_mutex_t		ph_is_full;
	pthread_mutex_t		ph_end_din;
	pthread_mutex_t		ph_init;
	pthread_mutex_t		ph_num_phs;
	pthread_mutex_t		ph_num_phs_init;
	t_philo				*philos;
	size_t				init_time;
	size_t				t_to_die;
	size_t				t_to_eat;
	size_t				t_to_sleep;
	short int			max_eat;
	short int			num_phs_init;
	short int			num_phs;
	short int			is_dead;
	short int			is_created;
	short int			end_din;
	short int			num_full;
};

// Validators
int		is_invalid_param(char **argv);
// Inits
int		init_table(t_table *table, int argc, char **argv);
int		init_struct_philos(t_table *table);
int		init_mutexes(t_table *table);
int		join_philos(t_table *table);
int		is_created(t_table *table);
// Routines
void	*single_routine(void *arg);
void	*routine(void *arg);
// Actions
int		eating(t_philo *philo);
int		sleep_n_think(t_philo *philo);
int		take_forks(t_philo *philo);
int		release_forks(t_philo *philo);
int		is_fullfiled(t_philo *philo);
// Finishers
int		finish_dinner(t_table *table);
// Utils
int		ft_issignal(char c);
int		ft_isspace(char c);
int		ft_strlen(char *str);
int		ft_isdigit(int c);
int		is_int(char *arg);
long	ft_atol(const char *nptr);
long	get_time(void);
// Prints
void	print_action(t_philo *philo, char *msg);
int		ft_print_error(char *error);
// monitoring
void	*monitoring(void *arg);
int		is_someone_dead(t_table *table, int is_philo);
int		verify_death(t_table *table);
int		is_end_dinner(t_table *table);

#endif