/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:54:39 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/22 13:48:43 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo_bonus.h"

// static int	ft_isnumber(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] < '0' || str[i] > '9')
// 		{
// 			write(1, "Wrong argument\n", 15);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	n_argc(int argc, t_args *args)
{
	if (argc < 5)
	{
		write(1, "Wrong arguments input\n", 22);
	}
	if (argc > 6)
	{
		write(1, "Wrong arguments input\n", 22);
	}
	if (argc < 5 || argc > 6)
	{
		free(args);
		args = NULL;
		return (1);
	}
	return (0);
}

