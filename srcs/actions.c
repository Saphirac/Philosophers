/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:51:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/30 18:54:25 by mcourtoi         ###   ########.fr       */
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
	if (ft_check_death(philo->p_arg) == DEAD)
		return (1);
	m_printf("is eating.", philo->p_arg, philo->id);
	pthread_mutex_lock(&philo->p_arg->meal);
	philo->last_meal = timestamp(philo->p_arg);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->p_arg->meal);
	if (ft_check_death(philo->p_arg) == 1)
		return (1);
	usleep(philo->time_eat * 1000);
	pthread_mutex_unlock(&philo->r_fork);
	philo->right_lock = UNLOCKED;
	pthread_mutex_unlock(philo->l_fork);
	philo->left_lock = UNLOCKED;
	return (0);
}

int	get_fork(t_philo *philo)
{
	if (ft_check_death(philo->p_arg) == 1)
		return (1);
	printf("death : %d\n", philo->p_arg->death);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->r_fork);
		philo->right_lock = LOCKED;
		m_printf("has taken a fork.", philo->p_arg, philo->id);
		if (ft_check_death(philo->p_arg) == 1)
			return (1);
		pthread_mutex_lock(philo->l_fork);
		philo->left_lock = LOCKED;
		m_printf("has taken a fork.", philo->p_arg, philo->id);
	}
	printf("death : %d\n", philo->p_arg->death);
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		philo->left_lock = LOCKED;
		m_printf("has taken a fork.", philo->p_arg, philo->id);
		if (ft_check_death(philo->p_arg) == 1)
			return (1);
		pthread_mutex_lock(&philo->r_fork);
		philo->right_lock = LOCKED;
		m_printf("has taken a fork.", philo->p_arg, philo->id);
	}
	return (0);
}
