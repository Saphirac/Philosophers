/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:25:43 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/17 02:35:31 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_death(t_arg *p_arg)
{
	int	i;

	i = -1;
	while (++i < p_arg->nb_philo - 1)
	{
		if ((timestamp(p_arg) - p_arg->philo[i].last_meal) > p_arg->time_die)
		{
			printf("[%d] Philosopher %d died\n", timestamp(p_arg), (i + 1));
			//free(p_arg->philo);
			exit(0);
		}
	}
	return (0);
}
