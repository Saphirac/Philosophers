/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:37:21 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/12/03 01:57:49 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_arg *p_arg)
{
	int	i;

	i = -1;
	if (create_mutex(p_arg) == 1)
		return (1);
	while (++i < p_arg->nb_philo)
		if (i % 2 == 1)
			if (pthread_create(&(p_arg->philo[i].th_philo),
					NULL, routine, (void *)&p_arg->philo[i]) != 0)
				return (1);
	usleep(100);
	i = -1;
	while (++i < p_arg->nb_philo)
		if (i % 2 == 0)
			if (pthread_create(&(p_arg->philo[i].th_philo),
					NULL, routine, (void *)&p_arg->philo[i]) != 0)
				return (1);
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
			return (printf("Mutex init failed.\n"), 1);
	}
	p_arg->philo[0].l_fork = &p_arg->philo[p_arg->nb_philo - 1].r_fork;
	i = 0;
	while (++i < p_arg->nb_philo)
		p_arg->philo[i].l_fork = &p_arg->philo[i - 1].r_fork;
	if (pthread_mutex_init((&p_arg->write), NULL) != 0)
		return (printf("Mutex init failed.\n"), 1);
	if (pthread_mutex_init((&p_arg->m_death), NULL) != 0)
		return (printf("Mutex init failed.\n"), 1);
	return (0);
}
