/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:25:43 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/12/03 01:59:03 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(int time, t_philo *philo)
{
	int	start;

	start = timestamp(philo->p_arg);
	while (timestamp(philo->p_arg) - start < time && philo->philo_stop == 0)
	{
		auto_check_death(philo);
		usleep(50);
	}
	return (0);
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
	pthread_mutex_lock(&p_arg->m_death);
	if (p_arg->death == ALIVE)
		printf("[%d] Philo %d %s\n", timestamp(p_arg), id, s);
	pthread_mutex_unlock(&p_arg->m_death);
	pthread_mutex_unlock(&p_arg->write);
}
