/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:28:34 by migonzal          #+#    #+#             */
/*   Updated: 2022/07/20 10:25:59 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	n_argc(int argc, t_args *args)
{
	if (argc < 5)
	{
		write(1, "Te faltan argumentos panita mio\n", 32);
	}
	if (argc > 6)
	{
		write(1, "Te has pachao con los argumentos mi brother\n", 44);
	}
	if (argc < 5 || argc > 6)
	{
		free(args);
		args = NULL;
		return (1);
	}
	return (0);
}

static int	ft_isnumber(char *str);

int	atoi_args(char **argv, t_args *args)
{
	int	i;
	int	m[5];

	i = 1;
	while (argv[i])
	{
		if (ft_isnumber(argv[i]))
		{
			free(args);
			args = NULL;
			return (1);
		}
		m[i - 1] = ft_atoi(argv[i]);
		if (m[i - 1] <= 0)
		{
			write(1, "Wrong argument\n", 15);
			free(args);
			return (1);
		}
		i++;
	}
	i = 0;
	rellenote(args, m, argv);
	return (0);
}

void	rellenote(t_args *args, int *m, char **argv)
{
	int	i;

	i = 0;
	args -> n_philo = m[i++];
	args -> t_die = m[i++];
	args -> t_eat = m[i++];
	args -> t_sleep = m[i++];
	if (argv[i + 1])
		args -> n_meal = m[i];
	else
		args -> n_meal = -1;
	args -> alive = true;
	args -> hungry = true;
	args -> satisfied = 0;
}

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			write(1, "Wrong argument\n", 15);
			return (1);
		}
		i++;
	}
	return (0);
}
