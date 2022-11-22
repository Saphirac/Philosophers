/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:59:48 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/22 23:07:47 by mcourtoi         ###   ########.fr       */
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

typedef struct s_philo t_philo;

typedef struct s_arg
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	int				start_time;
	pthread_mutex_t	m_death;
	int				death;
	pthread_mutex_t	write;
	t_philo		*philo;
}		t_arg;

typedef struct s_philo
{
	pthread_t		th_philo;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
	int				last_meal;
	int				id;
	t_arg			*p_arg;
}		t_philo;

long	ft_atoi(char *nptr);
int		is_digit(char *stack);
int		time_in_mill(void);
void	ft_error(char *str);
int		check_arg(char **av);
int		create_threads(t_arg *p_arg);
int		create_mutex(t_arg *p_arg);
int		get_fork(t_philo *philo);
void	philo_think(t_philo *philo);
int		philo_sleep(t_philo *philo);
int 	check_death(t_arg *p_arg);
int		timestamp(t_arg *p_arg);
void	*routine(void *philo);
int		philo_eat(t_philo *philo);




#endif