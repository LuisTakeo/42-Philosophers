/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaim-yu <tpaim-yu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:03:14 by tpaim-yu          #+#    #+#             */
/*   Updated: 2024/06/27 16:03:14 by tpaim-yu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine()
{
	int	*i;

	i = malloc(sizeof(int));
	*i = 0;
	printf("Começando a rotina\n");
	usleep(1000);
	printf("Terminando a rotina\n");
	return(&*i);
}

int	main(int argc, char **argv)
{
	pthread_t	t1;

	pthread_create(&t1, NULL, &routine, NULL);
	(void)argc;
	(void)argv;
	printf("Olar philo\n");
	return (EXIT_SUCCESS);
}