/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 10:21:13 by migonzal          #+#    #+#             */
/*   Updated: 2022/07/20 10:32:06 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(char *msg, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->args->mutex_print);
	time = ft_get_timestamp();
	if (philo->args->alive == true)
	{
		printf("\t%d ms\t%d\t%s\n", time - philo->args->zero_time, \
				philo->index, msg);
	}
	pthread_mutex_unlock(&philo->args->mutex_print);
}

void	*ft_routine(void *philo)
{
	t_philo	*ph;
	t_args	*args;

	ph = (t_philo *) philo;
	args = ph->args;
	ph->last_meal = ft_get_timestamp();
	if (ph->index % 2 == 0 || (ph -> index == args->n_philo && ph->index != 1))
		usleep(args -> t_eat * 500);
	while (1)
	{
		if (args->alive == false || ph->hungry == false)
			break ;
		if (ft_eating(ph))
			break ;
		ft_sleeping(ph);
		ft_print("is thinking", ph);
	}
	return (NULL);
}

int	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_print("has taken a fork (right)", philo);
	if (philo->args->n_philo == 1)
	{
		philo->last_meal = ft_get_timestamp();
		pthread_mutex_unlock(&philo->fork);
		while (ft_get_timestamp() - philo->last_meal \
				< philo->args->t_die)
			usleep(1000);
		return (1);
	}
	pthread_mutex_lock(&philo->left->fork);
	ft_print("has taken a fork (left)", philo);
	pthread_mutex_lock(&philo->args->mutex_life);
	ft_print("is eating", philo);
	philo->last_meal = ft_get_timestamp();
	pthread_mutex_unlock(&philo->args->mutex_life);
	usleep(philo->args->t_eat * 500);
	ft_keep_eating(philo);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->left->fork);
	return (0);
}

void	ft_keep_eating(t_philo *philo)
{
	while (1)
	{
		if (philo->args->alive == false)
			break ;
		if (ft_get_timestamp() - philo -> last_meal >= philo->args->t_eat)
			break ;
		usleep(500);
	}
	philo->meals++;
	if (philo->meals >= philo->args->n_meal && philo->args->n_meal != -1)
	{
		pthread_mutex_lock(&philo->args->mutex_satisfacion);
		philo->args->satisfied++;
		pthread_mutex_unlock(&philo->args->mutex_satisfacion);
		philo->hungry = false;
	}
}

void	ft_sleeping(t_philo *philo)
{
	int	start_sleep;

	start_sleep = ft_get_timestamp();
	ft_print("is sleeping", philo);
	usleep(philo->args->t_sleep * 500);
	while (1)
	{
		if (ft_get_timestamp() - start_sleep >= philo->args->t_sleep)
			break ;
		usleep(500);
	}
	return ;
}
