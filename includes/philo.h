/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:59:48 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/17 20:29:10 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define ALIVE 0
# define DEAD 1

typedef struct s_philo
{
	pthread_t		th_philo;
	pthread_mutex_t	fork;
	int				last_meal;
}		t_philo;

typedef struct s_arg
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	int				start_time;
	int				philo_id;
	int				test;
	ptread_mutex_t	m_death;
	int				death;
	pthread_mutex_t	write;
	t_philo		*philo;
}		t_arg;

long	ft_atoi(char *nptr);
int		is_digit(char *stack);
int		time_in_mill(void);
void	ft_error(char *str);
int		check_arg(char **av);
int		create_threads(t_arg *p_arg);
int		create_mutex(t_arg *p_arg);
int		get_fork(t_arg *p_arg, int p_id);
void	philo_think(t_arg *p_arg, int p_id);
int		philo_sleep(t_arg *p_arg, int p_id);
int 	check_death(t_arg *p_arg);
int		timestamp(t_arg *p_arg);
void	*routine(void *p_arg);
int		philo_eat(t_arg *p_arg, int p_id);




#endif