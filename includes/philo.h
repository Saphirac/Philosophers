/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:59:48 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/10/12 15:03:02 by mcourtoi         ###   ########.fr       */
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

typedef struct	s_philo
{
	pthread_t 		philo;
	pthread_mutex_t	fork;
	int				n_philo;
}		t_philo;

typedef struct s_arg
{
	int			nb_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			nb_eat;
	int			start_time;
	t_philo		*philo;
}		t_arg;


long	ft_atoi(char *nptr);
int		is_digit(char *stack);
int		time_in_mill(void);

#endif