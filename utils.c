/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecampos <pecampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:58:44 by pecampos          #+#    #+#             */
/*   Updated: 2023/07/31 17:43:51 by pecampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(560);
}

void	impr(char *text, t_philosopher *phil)
{
	int	x;

	usleep(10);
	pthread_mutex_lock(&phil->data->stop);
	x = phil->data->death_phil;
	if (x == 0 && phil->data->phil_com != phil->data->number_of_philosophers)
	{
		printf(text, (timestamp() - phil->data->count), phil->number);
	}
	pthread_mutex_unlock(&phil->data->stop);
	return ;
}

void	mutexs(t_philosopher *phil)
{
	pthread_mutex_lock(&phil->data->stop);
	pthread_mutex_lock(&phil->data->check_death);
	phil->data->death_phil = 1;
	pthread_mutex_unlock(&phil->data->check_death);
	pthread_mutex_unlock(&phil->data->stop);
}
