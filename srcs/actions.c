/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:51:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/17 02:34:11 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_arg *p_arg, int philo_id)
{
	printf("[%d] Philosophers %d is sleeping.\n", timestamp(p_arg), philo_id);
	usleep(p_arg->time_sleep * 1000);
}

void	philo_think(t_arg *p_arg, int philo_id)
{
	printf("[%d] Philosophers %d is thinking.\n", timestamp(p_arg), philo_id);
}

int	philo_eat(t_arg *p_arg, int p_id)
{
	printf("[%d] Philosophers %d is eating.\n", timestamp(p_arg), p_id);
	p_arg->philo[p_id - 1].last_meal = timestamp(p_arg);
	check_death(p_arg);
	usleep(p_arg->time_eat * 1000);
	check_death(p_arg);
	if (p_id == 1)
	{
		if (pthread_mutex_unlock(&p_arg->philo[p_id - 1].fork) != 0)
			return (1);
		if (pthread_mutex_unlock(&p_arg->philo[p_arg->nb_philo - 1].fork) != 0)
			return (1);
	}
	else
	{
		if (pthread_mutex_unlock(&p_arg->philo[p_id - 2].fork) != 0)
			return (1);
		if (pthread_mutex_unlock(&p_arg->philo[p_id - 1].fork) != 0)
			return (1);
	}
	return (0);
}

int	get_fork(t_arg *p_arg, int p_id)
{
	if (p_id == 1)
	{
		if (pthread_mutex_lock(&p_arg->philo[p_id - 1].fork) != 0)
			return (1);
		printf("[%d] Philo %d has taken a fork.\n", timestamp(p_arg), p_id);
		if (pthread_mutex_lock(&p_arg->philo[(p_arg->nb_philo) - 1].fork) != 0)
		{
			pthread_mutex_unlock(&p_arg->philo[p_id - 1].fork);
			return (1);
		}
	}
	else
	{
		if (pthread_mutex_lock(&p_arg->philo[p_id - 2].fork) != 0)
			return (1);
		printf("[%d] Philo %d has taken a fork.\n", timestamp(p_arg), p_id);
		if (pthread_mutex_lock(&p_arg->philo[p_id - 1].fork) != 0)
		{
			pthread_mutex_unlock(&p_arg->philo[p_id - 2].fork);
			return (1);
		}
	}
	return (philo_eat(p_arg, p_id));
}

