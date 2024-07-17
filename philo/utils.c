/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:58:29 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/07/09 14:58:29 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_issignal(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	is_int(char *arg)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (!arg[i])
		return (1);
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	if (!arg[i])
		return (1);
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (1);
	while (arg[i] == '0')
		i++;
	while (ft_isdigit(arg[i]))
	{
		i++;
		size++;
	}
	if (arg[i] || size > 10)
		return (1);
	return (0);
}
