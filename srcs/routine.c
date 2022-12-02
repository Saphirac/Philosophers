/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 07:55:14 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/12/02 06:27:08 by mcourtoi         ###   ########.fr       */
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
			p_arg->death = i + 1;
			pthread_mutex_unlock(&p_arg->m_death);
			// drop_all_forks(p_arg);
			usleep(500);
			//destroy_mutex(p_arg);
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
		if (p_arg->nb_eat != -1)
		{
			if (check_eat(p_arg) == 1)
				return (NULL);
		}
		usleep(200);
	}
}

void	*routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	while (ft_check_death(philo->p_arg, philo->id) == ALIVE)
	{
		if (ft_check_death(philo->p_arg, philo->id) != ALIVE)
			return (NULL);
		get_fork(philo);
		// if (ft_check_death(philo->p_arg, philo->id) != ALIVE)
		// 	return (NULL);
		philo_eat(philo);
		if (ft_check_death(philo->p_arg, philo->id) != ALIVE)
			return (NULL);
		philo_sleep(philo);
		if (ft_check_death(philo->p_arg, philo->id) != ALIVE)
			return (NULL);
		philo_think(philo);
		if (ft_check_death(philo->p_arg, philo->id) != ALIVE)
			return (NULL);
	}
	return (NULL);
}
