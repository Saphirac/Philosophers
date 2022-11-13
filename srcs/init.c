/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:37:21 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/13 19:02:17 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *v_arg)
{
	t_arg	*p_arg;

	p_arg = (t_arg *)v_arg;
	write(1, "routine\n", 8);
	while (1)
	{
		if (get_fork(p_arg, p_arg->philo_id) == 1)
			philo_think(p_arg, p_arg->philo_id);
		else
			philo_sleep(p_arg, p_arg->philo_id);
		check_death(p_arg);
	}
}

int	create_threads(t_arg *p_arg)
{
	int	i;

	i = -1;
	create_mutex(p_arg);
	while (++i < p_arg->nb_philo - 1)
	{
		p_arg->philo_id = i + 1;
		if (pthread_create(&(p_arg->philo[i].th_philo), NULL, &routine, (void *)p_arg) != 0)
			return (1);
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
