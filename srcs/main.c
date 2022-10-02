/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:59:28 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/07/28 17:37:31 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	set_params(char **av)
{
	t_philo	philo;

	philo.nb_philo = ft_atoi(av[1]);
	philo.time_die = ft_atoi(av[2]);
	philo.time_eat = ft_atoi(av[3]);
	philo.time_sleep = ft_atoi(av[4]);
	if (av[5])
		philo.number_eat = ft_atoi(av[5]);
	else
		philo.number_eat = -1;
	return (philo);
}

int	check_arg(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (is_digit(av[i]) == 0)
		{
			printf("Error : please input valid arguments\n");
			return (0);
		}
		if (ft_atoi(av[i]) < 0)
		{
			printf("Error : please only input positive arguments\n");
			return (0);
		}
	}
	return (1);
}

void	print_params(t_philo philo)
{
	printf("number of philo : %d\n", philo.nb_philo);
	printf("time to die : %d\n", philo.time_die);
	printf("time to eat : %d\n", philo.time_eat);
	printf("time to sleep : %d\n", philo.time_sleep);
	printf("number of eat : %d\n", philo.number_eat);
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac == 5 || ac == 6)
	{
		if (check_arg(av) == 1)
			philo = set_params(av);
		else
			return (1);
	}
	else
	{
		printf("Error : invalid number of arguments\n");
		return (1);
	}
	print_params(philo);
	return (0);
}
