/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:59:28 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/17 02:38:34 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_arg	set_params(char **av)
{
	t_arg	p_arg;
	int i = -1;

	p_arg.nb_philo = ft_atoi(av[1]);
	p_arg.time_die = ft_atoi(av[2]);
	p_arg.time_eat = ft_atoi(av[3]);
	p_arg.time_sleep = ft_atoi(av[4]);
	if (av[5])
		p_arg.nb_eat = ft_atoi(av[5]);
	else
		p_arg.nb_eat = -1;
	p_arg.start_time = time_in_mill();
	p_arg.philo = malloc(sizeof(t_philo) * p_arg.nb_philo);
	while (++i < p_arg.nb_philo)
		p_arg.philo[i].last_meal = 0;
	p_arg.philo_id = 0;
	p_arg.test = 0;
	if (!p_arg.philo)
		ft_error("Allocation Problem\n");
	return (p_arg);
}

int	main(int ac, char **av)
{
	t_arg	philo;

	if (ac != 5 && ac != 6)
		return (printf("Error : invalid number of arguments\n"));
	if (check_arg(av) == 0)
		return (1);
	philo = set_params(av);
	if (create_threads(&philo) == 1)
		return (printf("Problem with creating threads\n"));
	free(philo.philo);
	return (0);
}
