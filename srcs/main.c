/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:59:28 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/26 08:16:11 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_params_philo(char **av, t_arg *p_arg)
{
	int	i;
	
	i = -1;
	while (++i < p_arg->nb_philo)
	{
		p_arg->philo[i].id = i + 1;
		p_arg->philo[i].time_eat = ft_atoi(av[3]);
		p_arg->philo[i].time_sleep = ft_atoi(av[4]);
		p_arg->philo[i].last_meal = 0;
		p_arg->philo[i].p_arg = p_arg;
		p_arg->philo[i].nb_eat = 0;
	}
}

t_arg	*set_params(char **av, t_arg *p_arg)
{
	p_arg->nb_philo = ft_atoi(av[1]);
	p_arg->time_die = ft_atoi(av[2]);
	if (av[5])
		p_arg->nb_eat = ft_atoi(av[5]);
	else
		p_arg->nb_eat = -1;
	p_arg->start_time = time_in_mill();
	p_arg->death = ALIVE;
	p_arg->philo = malloc(sizeof(t_philo) * p_arg->nb_philo);
	if (!p_arg->philo)
		return (0);
	set_params_philo(av, p_arg);
	return (p_arg);
}

int	main(int ac, char **av)
{	
	t_arg	p_arg;
	t_arg	philo;

	if (ac != 5 && ac != 6)
		return (ft_return("Error : invalid number of arguments\n", 1));
	if (check_arg(av) == 0)
		return (1);
	philo = *set_params(av, &p_arg);
	if (create_threads(&philo) == 1)
		return (ft_return("Problem with creating threads\n", 1));
	free(philo.philo);
	return (0);
}
