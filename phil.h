/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecampos <pecampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:27:03 by pecampos          #+#    #+#             */
/*   Updated: 2023/07/31 17:27:01 by pecampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_H
# define PHIL_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_data;

typedef struct s_philosopher
{
	int				number;
	int				num_com;
	int				check;
	long long		lasteat;
	struct s_data	*data;
	pthread_t		t;
	pthread_t		lifecontroller;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;

}					t_philosopher;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				forks;
	long long		count;
	int				com;
	int				error;
	int				death_phil;
	int				phil_com;
	pthread_mutex_t	stop;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat;
	pthread_mutex_t	check_death;
	t_philosopher	*philosophers;
}					t_data;

int					ft_atoi(const char *str);
void				phil_init(t_data *data);
void				init(t_data *data, char **argv, int argc);
void				*phil_life(void *phi);
int					is_dead(t_philosopher *phil);
void				comer(t_philosopher *phil);
void				fork_controller(t_philosopher *phil);
void				*life_cotroller(void *phi);
void				freeall(t_data *data);
int					check_num(char **argv);
void				impr(char *text, t_philosopher *phil);
void				ft_usleep(int ms);
long long			timestamp(void);
void				mutexs(t_philosopher *phil);

#endif