/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecampos <pecampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:42:17 by pecampos          #+#    #+#             */
/*   Updated: 2023/08/01 10:41:40 by pecampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	check_num(char **argv)
{
	int	x;
	int	y;

	x = 0;
	y = 1;
	while (argv[y])
	{
		while (argv[y][x] != '\0')
		{
			if (argv[y][x] < '0' || argv[y][x] > '9')
				return (1);
			x++;
		}
		y++;
		x = 0;
	}
	return (0);
}

void	freeall(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->philosophers[i].left_fork);
		pthread_mutex_destroy(data->philosophers[i].right_fork);
		i++;
	}
	free(data->philosophers);
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->stop);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc < 5 || argc > 6) || check_num(argv) == 1)
	{
		printf("ERROR\n");
		return (0);
	}
	init(&data, argv, argc);
	phil_init(&data);
	freeall(&data);
}
