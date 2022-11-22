/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:51:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/23 00:04:28 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philo *philo)
{
	printf("[%d] Philosophers %d is sleeping.\n", timestamp(philo->p_arg), philo->id);
	usleep(1000);
	if (check_death(philo->p_arg) == 2)
		return (2);
	return (0);
}

void	philo_think(t_philo *philo)
{
	printf("[%d] Philosophers %d is thinking.\n", timestamp(philo->p_arg), philo->id);
}

int	philo_eat(t_philo *philo)
{
	printf("[%d] Philosophers %d is eating.\n", timestamp(philo->p_arg), philo->id);
	philo->last_meal = timestamp(philo->p_arg);
	usleep(1000);
//	if (check_death(philo->p_arg) == 2)
//		return (2);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	printf("a plu fork\n");
	return (0);
}

int	get_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->r_fork);
		printf("[%d] Philo %d has taken a fork.\n", timestamp(philo->p_arg), philo->id);
		pthread_mutex_lock(philo->l_fork);
		printf("[%d] Philo %d has taken a fork.\n", timestamp(philo->p_arg), philo->id);
	}
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		printf("[%d] Philo %d has taken a fork.\n", timestamp(philo->p_arg), philo->id);
		pthread_mutex_lock(&philo->r_fork);
		printf("[%d] Philo %d has taken a fork.\n", timestamp(philo->p_arg), philo->id);
	}

	return (philo_eat(philo));
}
