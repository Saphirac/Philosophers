/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:59:28 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/10/13 17:37:57 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_arg	set_params(char **av)
{
	t_arg	p_arg;

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
	if (!p_arg.philo)
		ft_error("Allocation Problem\n");
	return (p_arg);
}

void	print_params(t_arg philo)
{
	printf("number of philo : %d\n", philo.nb_philo);
	printf("time to die : %d\n", philo.time_die);
	printf("time to eat : %d\n", philo.time_eat);
	printf("time to sleep : %d\n", philo.time_sleep);
	printf("number of eat : %d\n", philo.nb_eat);
}

int	main(int ac, char **av)
{
	t_arg	philo;

	if (ac != 5 && ac != 6)
		return (printf("Error : invalid number of arguments\n"));
	if (check_arg(av) == 0)
		return (1);
	philo = set_params(av);
	print_params(philo);
	if (create_threads(&philo) == 1)
		return (printf("Problem with creating threads\n"));
	return (0);
}
