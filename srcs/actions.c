/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:51:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/29 21:37:00 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philo *philo)
{
	if (ft_check_death(philo->p_arg) == 1)
		return (1);
	m_printf("is sleeping.", philo->p_arg, philo->id);
	usleep(philo->time_sleep * 1000);
	return (0);
}

void	philo_think(t_philo *philo)
{
	m_printf("is thinking.", philo->p_arg, philo->id);
}

int	philo_eat(t_philo *philo)
{
	if (ft_check_death(philo->p_arg) == 1)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	m_printf("is eating.", philo->p_arg, philo->id);
	pthread_mutex_lock(&philo->p_arg->meal);
	philo->last_meal = timestamp(philo->p_arg);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->p_arg->meal);
	usleep(philo->time_eat * 1000);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (0);
}

int	get_fork(t_philo *philo)
{
	if (ft_check_death(philo->p_arg) == 1)
		return (1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->r_fork);
		m_printf("has taken a fork.", philo->p_arg, philo->id);
		if (ft_check_death(philo->p_arg) == 1)
		{
			pthread_mutex_unlock(&philo->r_fork);
			return (1);
		}
		pthread_mutex_lock(philo->l_fork);
		m_printf("has taken a fork.", philo->p_arg, philo->id);
	}
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		m_printf("has taken a fork.", philo->p_arg, philo->id);
		if (ft_check_death(philo->p_arg) == 1)
		{
			pthread_mutex_unlock(philo->l_fork);
			return (1);
		}
		pthread_mutex_lock(&philo->r_fork);
		m_printf("has taken a fork.", philo->p_arg, philo->id);
	}
	return (0);
}
