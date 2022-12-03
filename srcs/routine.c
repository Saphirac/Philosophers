/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 07:55:14 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/12/03 02:00:05 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	auto_check_death(t_philo *philo)
{
	if (ft_check_death(philo->p_arg) != 0)
	{
		philo->philo_stop = 1;
		return (1);
	}
	if (timestamp(philo->p_arg) - philo->last_meal > philo->p_arg->time_die)
	{
		if (ft_check_death(philo->p_arg) == 0)
		{
			m_printf("died.\n", philo->p_arg, philo->id);
			pthread_mutex_lock(&philo->p_arg->m_death);
			philo->p_arg->death = philo->id;
			pthread_mutex_unlock(&philo->p_arg->m_death);
		}
		philo->philo_stop = 1;
		return (1);
	}
	if (philo->eat_done == philo->p_arg->nb_eat)
	{
		philo->philo_stop = 1;
		return (1);
	}
	return (0);
}

void	one_philo(t_philo *philo)
{
	m_printf("has taken a fork.\n", philo->p_arg, philo->id);
	ft_usleep(philo->p_arg->time_die, philo);
	m_printf("died.\n", philo->p_arg, philo->id);
}

void	*routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	if (philo->p_arg->nb_philo == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	while (auto_check_death(philo) == 0 || philo->philo_stop == 0)
	{
		if (auto_check_death(philo) != 0 || philo->philo_stop != 0)
			return (NULL);
		get_fork(philo);
		philo_eat(philo);
		if (auto_check_death(philo) != 0 || philo->philo_stop != 0)
			return (NULL);
		philo_sleep(philo);
		if (auto_check_death(philo) != 0 || philo->philo_stop != 0)
			return (NULL);
		philo_think(philo);
		if (auto_check_death(philo) != 0 || philo->philo_stop != 0)
			return (NULL);
	}
	return (NULL);
}
