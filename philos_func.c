/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:44:45 by migonzal          #+#    #+#             */
/*   Updated: 2022/07/20 10:22:52 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_free_list(t_philo **lst_philo)
{
	t_philo	*aux;
	t_philo	*aux2;

	aux = *lst_philo;
	while (aux)
	{
		aux2 = aux;
		aux = aux -> right;
		free(aux2);
	}
}

int	ft_create_philos(t_philo **lst_philo, t_args *args)
{
	int		i;
	t_philo	*aux;

	i = 0;
	while (i < args -> n_philo)
	{
		aux = ft_lstnew(i + 1);
		if (!aux)
		{
			ft_free_list(lst_philo);
			free(args);
			return (1);
		}
		else
			ft_lstadd_back(lst_philo, aux);
		i++;
	}
	return (0);
}

void	init_philos(t_philo *lst_philo, t_args *args)
{
	int	i;

	i = 1;
	while (i <= args -> n_philo)
	{
		lst_philo -> args = args;
		lst_philo -> hungry = true;
		lst_philo -> meals = 0;
		lst_philo -> last_meal = 0;
		lst_philo = lst_philo -> right;
		i++;
	}
}

void	ft_free_philos(t_philo *lst_philo, t_args *args)
{
	t_philo	*aux;
	t_philo	*aux2;
	int		i;

	i = 1;
	aux = lst_philo;
	while (i < args -> n_philo)
	{
		aux2 = aux;
		aux = aux -> right;
		free(aux2);
		i++;
	}
	free(aux);
	free(args);
	return ;
}
