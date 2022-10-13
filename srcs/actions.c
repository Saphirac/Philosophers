/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:51:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2022/10/13 22:49:24 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	philo_sleep(t_arg *p_arg, int philo_id)
{
	printf("[%d] Philosophers %d is sleeping.\n", timestamp(p_arg), philo_id);
	usleep(p_arg->time_sleep * 1000);
}

void	philo_thinking(t_arg *p_arg, int philo_id)
{
	int	timestamp;
	
	timestamp = time_in_mill() - p_arg->start_time;
	printf("[%d] Philosophers %d is thinking.\n", timestamp(p_arg), philo_id);
}

void get_fork(t_arg *p_arg)
{
	int	i;

	i = -1;
	while (i < p_arg->nb_philo)
	{
		if (pthread_mutex_lock(&(p_arg->philo[i].fork)) != 0)
			return (1);
		i++;
	}
	printf("[%d] Philosophers %d is eating.\n", timestamp(p_arg), philo_id);
}