/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:08:46 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/11/26 18:42:21 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *nptr)
{
	long	i;
	long	s;
	long	sum;

	i = 0;
	s = 1;
	sum = 0;
	while (nptr[i] && (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		sum = sum * 10 + (nptr[i] - '0');
		i++;
	}
	return (sum * s);
}

int	is_digit(char *stack)
{
	int	i;

	i = -1;
	while (stack[i + 1] == '-' || stack[i + 1] == '+')
		i++;
	while (stack[++i])
		if (!(stack[i] >= '0' && stack[i] <= '9'))
			return (0);
	if (i >= 10 && (ft_atoi(stack) > 2147483647
			|| ft_atoi(stack) < -2147483648))
		return (0);
	return (1);
}

int	time_in_mill(void)
{
	struct timeval	tv;
	int				mill;

	gettimeofday(&tv, NULL);
	mill = tv.tv_sec * 1000 + (tv.tv_usec) / 1000;
	return (mill);
}

int	ft_check_death(t_arg *p_arg)
{
	pthread_mutex_lock(&p_arg->m_death);
	if (p_arg->death == DEAD)
		return (1);
	pthread_mutex_unlock(&p_arg->m_death);
	return (0);
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
