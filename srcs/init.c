/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:37:21 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/23 00:07:38 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *v_philo)
{
	t_philo	*philo;
	int 	i;

	philo = (t_philo *)v_philo;
	philo->last_meal = 0;
	i = 0;
	printf("time sleep : %d\n", philo->p_arg->time_sleep);
	//while (i == 0 || i == 1)
	//{
		i = get_fork(philo);
		philo_think(philo);
		i = philo_sleep(philo);
		i = check_death(philo->p_arg);
	//}
	(void)i;
	return (NULL);
}

int	create_threads(t_arg *p_arg)
{
	int	i;

	i = -1;
	create_mutex(p_arg);
	printf("time sleep : %d\n", p_arg->time_sleep);
	while (++i < p_arg->nb_philo)
		if (pthread_create(&(p_arg->philo[i].th_philo), NULL, routine, (void *)&p_arg->philo[i]) != 0)
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
		if(pthread_mutex_init((&p_arg->philo[i].r_fork), NULL) != 0)
			ft_error("Mutex init failed\n");
	}
	p_arg->philo[0].l_fork = &p_arg->philo[p_arg->nb_philo - 1].r_fork;
	i = 0;
	while (++i < p_arg->nb_philo)
		p_arg->philo[i].l_fork = &p_arg->philo[i - 1].r_fork;
	return (0);
}
