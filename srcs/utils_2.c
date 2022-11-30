/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:25:43 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/30 19:07:57 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat(t_arg *p_arg)
{
	int	i;

	i = 0;
	while (i < p_arg->nb_philo)
	{
		pthread_mutex_lock(&p_arg->meal);
		if (p_arg->philo[i].nb_eat < p_arg->nb_eat)
			return (0);
		pthread_mutex_unlock(&p_arg->meal);
		i++;
	}
	pthread_mutex_lock(&p_arg->m_death);
	p_arg->death = DEAD;
	pthread_mutex_unlock(&p_arg->m_death);
	return (1);
}

int	ft_usleep(int time)
{
	
}

int	timestamp(t_arg *p_arg)
{
	int	timestamp;

	timestamp = time_in_mill() - p_arg->start_time;
	return (timestamp);
}

void	m_printf(char *s, t_arg *p_arg, int id)
{
	pthread_mutex_lock(&p_arg->write);
	//pthread_mutex_lock(&p_arg->m_death);
	//if (p_arg->death == ALIVE)
	printf("[%d] Philo %d %s\n", timestamp(p_arg), id, s);
	//pthread_mutex_unlock(&p_arg->m_death);
	pthread_mutex_unlock(&p_arg->write);
}

void	drop_all_forks(t_arg *p_arg)
{
	int i;

	i = 0;
	while (i < p_arg->nb_philo)
	{
		if (p_arg->philo[i].right_lock == LOCKED)
			pthread_mutex_unlock(&p_arg->philo[i].r_fork);
		if (p_arg->philo[i].left_lock == LOCKED)
			pthread_mutex_unlock(p_arg->philo[i].l_fork);
		i++;
	}
}