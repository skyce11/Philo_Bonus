/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 11:18:13 by migonzal          #+#    #+#             */
/*   Updated: 2022/07/19 11:41:20 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_timestamp(void)
{
	int				res;
	struct timeval	time;

	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}

int	main(int argc, char **argv)
{
	t_args	*args;
	t_philo	*lst_philo;

	lst_philo = 0;
	args = malloc (sizeof(t_args));
	if (!args)
		return (1);
	if (ft_main_aux1(argc, argv, &lst_philo, args))
		return (2);
	args -> zero_time = ft_get_timestamp();
	if (ft_main_aux2(lst_philo, args))
		return (3);
	ft_free_philos(lst_philo, args);
	return (0);
}

int	ft_main_aux1(int argc, char **argv, t_philo **lst_philo, t_args *args)
{
	if (n_argc(argc, args))
		return (2);
	if (atoi_args(argv, args))
		return (2);
	if (ft_create_philos(lst_philo, args))
		return (3);
	ft_link_list(*lst_philo);
	init_philos(*lst_philo, args);
	if (ft_create_mutex(*lst_philo, args))
	{
		ft_free_philos(*lst_philo, args);
		return (4);
	}
	return (0);
}

int	ft_main_aux2(t_philo *lst_philo, t_args *args)
{
	if (ft_create_threads(lst_philo, &ft_routine))
	{
		ft_free_philos(lst_philo, args);
		return (5);
	}
	usleep(800);
	ft_check_status(lst_philo, args);
	if (ft_join_threads(lst_philo, args))
	{
		ft_free_philos(lst_philo, args);
		return (6);
	}
	if (ft_destroy_mutex(lst_philo, args))
	{
		ft_free_philos(lst_philo, args);
		return (7);
	}
	return (0);
}
