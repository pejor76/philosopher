/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecampos <pecampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:08:24 by pecampos          #+#    #+#             */
/*   Updated: 2023/07/31 17:04:39 by pecampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	phil_init(t_data *data)
{
	int	i;

	i = -1;
	data->count = timestamp();
	while (++i < data->number_of_philosophers)
	{
		data->philosophers[i].lasteat = 0;
		data->philosophers[i].number = i + 1;
		data->philosophers[i].check = 0;
		data->philosophers[i].data = data;
		data->philosophers[i].right_fork = NULL;
		pthread_mutex_init(&(data->philosophers[i].left_fork), NULL);
		if (i == data->number_of_philosophers - 1)
			data->philosophers[i].right_fork = &data->philosophers[0].left_fork;
		else
			data->philosophers[i].right_fork = &data->philosophers[i
				+ 1].left_fork;
		data->philosophers[i].num_com = 0;
		pthread_create(&data->philosophers[i].t, NULL, &phil_life,
			&(data->philosophers[i]));
	}
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_join(data->philosophers[i].t, NULL);
}

void	init(t_data *data, char **argv, int argc)
{
	pthread_mutex_init(&(data->mutex), NULL);
	pthread_mutex_init(&(data->eat), NULL);
	pthread_mutex_init(&(data->check_death), NULL);
	pthread_mutex_init(&(data->stop), NULL);
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->philosophers = malloc(sizeof(t_philosopher)
			* data->number_of_philosophers);
	data->forks = data->number_of_philosophers - 1;
	data->death_phil = 0;
	data->com = -1;
	data->error = 0;
	data->phil_com = 0;
	if (argc == 6)
		data->com = ft_atoi(argv[5]);
}
