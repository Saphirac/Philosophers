/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:59:48 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/12/02 06:05:44 by mcourtoi         ###   ########.fr       */
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
# define UNLOCKED 0
# define LOCKED 1

typedef struct s_philo	t_philo;

typedef struct s_arg
{
	int				nb_philo;
	int				time_die;
	int				nb_eat;
	int				start_time;
	pthread_mutex_t	m_death;
	int				death;
	pthread_mutex_t	write;
	pthread_mutex_t	meal;
	//pthread_mutex_t	check_nb;
	t_philo			*philo;
	pthread_t		monitor;
}		t_arg;

typedef struct s_philo
{
	pthread_t		th_philo;
	pthread_mutex_t	r_fork;
	int				right_lock;
	pthread_mutex_t	*l_fork;
	int				left_lock;
	int				last_meal;
	int				id;
	int				time_sleep;
	int				time_eat;
	int				nb_eat;
	t_arg			*p_arg;
}		t_philo;

long	ft_atoi(char *nptr);
int		is_digit(char *stack);
int		time_in_mill(void);
int		check_arg(char **av);
int		create_threads(t_arg *p_arg);
int		create_mutex(t_arg *p_arg);
int		get_fork(t_philo *philo);
void	philo_think(t_philo *philo);
int		philo_sleep(t_philo *philo);
void	*check_death(void *p_arg);
int		timestamp(t_arg *p_arg);
void	*routine(void *philo);
int		philo_eat(t_philo *philo);
void	m_printf(char *s, t_arg *p_arg, int id);
int		ft_check_death(t_arg *p_arg, int id);
int		check_eat(t_arg *p_arg);
void	destroy_mutex(t_arg *p_arg);
void	*routine(void *v_philo);
void	drop_all_forks(t_arg *p_arg);
int		ft_usleep(int time, t_arg *p_arg);

#endif