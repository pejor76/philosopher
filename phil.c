/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecampos <pecampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:09:21 by pecampos          #+#    #+#             */
/*   Updated: 2023/07/31 17:26:43 by pecampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	is_dead(t_philosopher *phil)
{
	pthread_mutex_lock(&phil->data->check_death);
	if (phil->data->death_phil == 1)
	{
		pthread_mutex_unlock(&phil->data->check_death);
		return (2);
	}
	if ((timestamp() - phil->data->count)
		- phil->lasteat > phil->data->time_die && phil->data->death_phil == 0)
	{
		pthread_mutex_unlock(&phil->data->check_death);
		return (1);
	}
	pthread_mutex_unlock(&phil->data->check_death);
	return (0);
}

void	comer(t_philosopher *phil)
{
	impr("%lld %d is eating\n", phil);
	pthread_mutex_lock(&phil->data->eat);
	pthread_mutex_lock(&phil->data->check_death);
	phil->lasteat = timestamp() - phil->data->count;
	pthread_mutex_unlock(&phil->data->check_death);
	phil->num_com++;
	pthread_mutex_lock(&phil->data->mutex);
	if (phil->num_com >= phil->data->com
		&& phil->data->com != -1 && phil->check == 0)
	{
			phil->check++;
		pthread_mutex_lock(&phil->data->stop);
			phil->data->phil_com++;
		pthread_mutex_unlock(&phil->data->stop);
	}
	pthread_mutex_unlock(&phil->data->mutex);
	pthread_mutex_unlock(&phil->data->eat);
	ft_usleep(phil->data->time_eat);
	pthread_mutex_unlock(phil->right_fork);
	pthread_mutex_unlock(&phil->left_fork);
	impr("%lld %d is sleeping\n", phil);
	ft_usleep(phil->data->time_sleep);
	impr("%lld %d is thinking\n", phil);
}

void	fork_controller(t_philosopher *phil)
{
	pthread_mutex_lock(phil->right_fork);
	impr("%lld %d has taken a fork\n", phil);
	if (phil->data->number_of_philosophers == 1)
	{
		ft_usleep(phil->data->time_die * 2);
		return ;
	}
	pthread_mutex_lock(&phil->left_fork);
	impr("%lld %d has taken a fork\n", phil);
}

void	*life_cotroller(void *phi)
{
	t_philosopher	*phil;
	int				out;
	int				com;

	out = 0;
	com = 0;
	phil = (t_philosopher *)phi;
	while (out == 0
		&& com != phil->data->number_of_philosophers)
	{
		ft_usleep((phil->data->time_die + 1));
		pthread_mutex_lock(&phil->data->eat);
		pthread_mutex_lock(&phil->data->mutex);
		if (is_dead(phil) == 1)
		{
			impr("%lld %d died\n", phil);
			com = phil->data->phil_com;
			mutexs(phil);
			out++;
		}
		pthread_mutex_unlock(&phil->data->mutex);
		pthread_mutex_unlock(&phil->data->eat);
	}
	return (NULL);
}

void	*phil_life(void *phi)
{
	t_philosopher	*phil;
	pthread_t		t;
	int				i;

	i = -1;
	phil = (t_philosopher *)phi;
	if (phil->number % 2 == 0)
		ft_usleep(10);
	pthread_create(&t, NULL, life_cotroller, phil);
	pthread_mutex_lock(&phil->data->mutex);
	while (is_dead(phil) == 0
		&& phil->data->phil_com != phil->data->number_of_philosophers)
	{
		pthread_mutex_unlock(&phil->data->mutex);
		fork_controller(phil);
		comer(phil);
		pthread_detach(t);
		pthread_mutex_lock(&phil->data->mutex);
	}
	pthread_mutex_unlock(&phil->data->mutex);
	pthread_join(t, NULL);
	return (NULL);
}
