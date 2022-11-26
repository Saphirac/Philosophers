/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:37:21 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/26 19:00:45 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	while (philo->p_arg->death == ALIVE)
	{
		if (ft_check_death(philo->p_arg) == 1)
		return (NULL);
		if (get_fork(philo) == 0)
			philo_eat(philo);
		if (ft_check_death(philo->p_arg) == 1)
		return (NULL);
		philo_think(philo);
		if (ft_check_death(philo->p_arg) == 1)
		return (NULL);
		philo_sleep(philo);
	}
	return (NULL);
}

void	*check_death(void *v_arg)
{
	t_arg	*p_arg;
	int		i;

	p_arg = (t_arg *)v_arg;
	while (p_arg->death == ALIVE)
	{
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
				return (NULL);
			}
			pthread_mutex_unlock(&p_arg->meal);
			i++;
		}
		if (p_arg->nb_eat != -1)
			if (check_eat(p_arg) == 1)
				return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	create_threads(t_arg *p_arg)
{
	int	i;

	i = -1;
	create_mutex(p_arg);
	while (++i < p_arg->nb_philo)
		if (pthread_create(&(p_arg->philo[i].th_philo),
				NULL, routine, (void *)&p_arg->philo[i]) != 0)
			return (1);
	if (pthread_create(&(p_arg->monitor),
			NULL, check_death, (void *)p_arg) != 0)
		return (1);
	pthread_join(p_arg->monitor, NULL);
	i = -1;
	while (++i < p_arg->nb_philo)
		if (pthread_join(p_arg->philo[i].th_philo, NULL) != 0)
			return (1);
	return (0);
}

int	create_mutex(t_arg *p_arg)
{
	int	i;

	i = -1;
	while (++i < p_arg->nb_philo)
	{
		p_arg->philo[i].p_arg = p_arg;
		if (pthread_mutex_init((&p_arg->philo[i].r_fork), NULL) != 0)
			return (ft_return("Mutex init failed\n", 1));
	}
	p_arg->philo[0].l_fork = &p_arg->philo[p_arg->nb_philo - 1].r_fork;
	i = 0;
	while (++i < p_arg->nb_philo)
		p_arg->philo[i].l_fork = &p_arg->philo[i - 1].r_fork;
	if (pthread_mutex_init((&p_arg->write), NULL) != 0)
		return (ft_return("Mutex init failed\n", 1));
	if (pthread_mutex_init((&p_arg->m_death), NULL) != 0)
		return (ft_return("Mutex init failed\n", 1));
	if (pthread_mutex_init((&p_arg->meal), NULL) != 0)
		return (ft_return("Mutex init failed\n", 1));
	return (0);
}
