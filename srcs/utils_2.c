/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:25:43 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/24 04:38:49 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_arg *p_arg)
{
	int	i;

	i = 0;
	while (i < p_arg->nb_philo)
	{
		pthread_mutex_destroy(&p_arg->philo[i].r_fork);
		i++;
	}
	pthread_mutex_destroy(&p_arg->m_death);
	pthread_mutex_destroy(&p_arg->write);
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
			if ((timestamp(p_arg) - p_arg->philo[i].last_meal)
				> p_arg->time_die)
			{
				m_printf("died", p_arg, (i + 1));
				pthread_mutex_lock(&p_arg->m_death);
				p_arg->death = DEAD;
				pthread_mutex_unlock(&p_arg->m_death);
				destroy_mutex(p_arg);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int	timestamp(t_arg *p_arg)
{
	int	timestamp;

	timestamp = time_in_mill() - p_arg->start_time;
	return (timestamp);
}

void	m_printf(const char *s, t_arg *p_arg, int id)
{
	pthread_mutex_lock(&p_arg->write);
	if (p_arg->death == ALIVE)
		printf("[%d] Philo %d %s\n", timestamp(p_arg), id, s);
	pthread_mutex_unlock(&p_arg->write);
}
