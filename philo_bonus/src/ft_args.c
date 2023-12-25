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
bool only_digits(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}


int	integer_atoi(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}


bool is_valid_input(int argc, char **argv)
{
	int i;
	//int n;

	i = 1;
	while(i < argc)
	{
		if (!only_digits(argv[i]))
			return (print_msg("%s invalid input: %s\n: ", argv[i], false));
	//	n = integer_atoi(argv[i]);
	//	if (i == 1 && (n <= 0 || n > 200))
	//		return (print_msg("%s invalid input: %s\n", "200", false));
	//	if (i != 1 && n == -1)
	//		return (print_msg("%s invalid input: %s\n", argv[i], false));
		i++;
	}
	return (true);
}


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

