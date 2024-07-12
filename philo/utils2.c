/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:57:16 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/07/11 14:57:16 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	long	result;
	int		i;
	int		is_negative;

	is_negative = 0;
	result = 0;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (ft_issignal(nptr[i]))
	{
		if (nptr[i] == '-')
			is_negative = 1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	if (is_negative)
		result *= -1;
	return (result);
}

long	get_time(void)
{
	t_timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

int	ft_print_error(char *error)
{
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}
