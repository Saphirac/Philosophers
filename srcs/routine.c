/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 07:55:14 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/28 21:03:50 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_died(t_arg *p_arg)
{
	int	i;

	i = 0;
	while (i < p_arg->nb_philo)
	{
		pthread_mutex_lock(&p_arg->meal);
		if ((timestamp(p_arg) - p_arg->philo[i].last_meal)
			> p_arg->time_die)
		{
			pthread_mutex_unlock(&p_arg->meal);
			m_printf("died", p_arg, (i + 1));
			pthread_mutex_lock(&p_arg->m_death);
			p_arg->death = DEAD;
			pthread_mutex_unlock(&p_arg->m_death);
			usleep(1000);
			destroy_mutex(p_arg);
			return (1);
		}
		pthread_mutex_unlock(&p_arg->meal);
		i++;
	}
	return (0);
}

void	*check_death(void *v_arg)
{
	t_arg	*p_arg;

	p_arg = (t_arg *)v_arg;
	while (1)
	{
		if (check_philo_died(p_arg) == 1)
			return (NULL);
		pthread_mutex_lock(&p_arg->meal);
		if (p_arg->nb_eat != -1)
		{
			pthread_mutex_unlock(&p_arg->meal);
			if (check_eat(p_arg) == 1)
				return (NULL);
		}
		pthread_mutex_unlock(&p_arg->meal);
		usleep(1000);
	}
	return (NULL);
}

void	*routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	while (ft_check_death(philo->p_arg) == 0)
	{
		if (ft_check_death(philo->p_arg) == 1)
			return (NULL);
		if (get_fork(philo) == 0)
			philo_eat(philo);
		if (ft_check_death(philo->p_arg) == 1)
			return (NULL);
		philo_sleep(philo);
		if (ft_check_death(philo->p_arg) == 1)
			return (NULL);
		philo_think(philo);
		if (ft_check_death(philo->p_arg) == 1)
			return (NULL);
	}
	return (NULL);
}
