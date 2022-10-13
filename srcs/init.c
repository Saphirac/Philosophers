/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:37:21 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/10/13 17:43:44 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *i)
{
	int	*o;

	o = (int *)i;
	printf("i : %d\n", *o);
	return (i);
}

int	create_threads(t_arg *p_arg)
{
	int	i;

	i = -1;
	while (++i < p_arg->nb_philo)
	{
		if (pthread_create(&(p_arg->philo[i].th_philo), NULL, routine, &i) != 0)
			return (1);
		if (pthread_join(p_arg->philo[i].th_philo, NULL) != 0)
			return (2);
		p_arg->philo[i].n_philo = i;
	}
	return (0);
}

int	create_mutex(t_arg philo)
{
	
}
