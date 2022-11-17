/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:37:21 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/17 02:43:19 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *v_arg)
{
	t_arg	*p_arg;
	int		p_id;

	p_arg = (t_arg *)v_arg;
	p_id = p_arg->philo_id;
	p_arg->philo[p_id - 1].last_meal = 0;
	while (1)
	{
		if (get_fork(p_arg, p_id) == 1)
			philo_think(p_arg, p_id);
		else
			philo_sleep(p_arg, p_id);
		printf("last_meal %d : %d\n", p_id, p_arg->philo[p_id - 1].last_meal);
		check_death(p_arg);
	}
	return (NULL);
}

int	create_threads(t_arg *p_arg)
{
	int	i;

	i = -1;
	create_mutex(p_arg);
	while (++i < p_arg->nb_philo)
	{
		p_arg->philo_id = i + 1;
		if (pthread_create(&(p_arg->philo[i].th_philo), NULL, routine, (void *)p_arg) != 0)
			return (1);
	}
	i = -1;
	while (++i < p_arg->nb_philo)
	{
		if (pthread_join(p_arg->philo[i].th_philo, NULL) != 0)
			return (1);
	}
	return (0);
}

int	create_mutex(t_arg *p_arg)
{
	int	i;

	i = -1;
	while (++i < p_arg->nb_philo)
	{
		if(pthread_mutex_init((&p_arg->philo[i].fork), NULL) != 0)
			ft_error("Mutex init failed\n");
	}
	return (0);
}
