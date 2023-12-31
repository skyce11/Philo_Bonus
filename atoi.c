/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 13:02:48 by migonzal          #+#    #+#             */
/*   Updated: 2022/07/20 10:27:14 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_overflows(unsigned long long n, int neg)
{
	if (neg == -1 && n > 9223372036854775807)
		return (0);
	if (neg == 1 && n > 9223372036854775807)
		return (-1);
	return (n);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	n;
	int					neg;

	i = 0;
	neg = 1;
	n = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == '\v' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	n = check_overflows(n, neg);
	return (n * neg);
}
