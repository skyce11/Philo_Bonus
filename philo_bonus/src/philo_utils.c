/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:36:34 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/26 14:47:16 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while (src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}

char	*ft_utoa(unsigned int n, size_t len)
{
	char	*aux;

	aux = malloc(sizeof * aux * (len +1));
	if (!aux)
		return (NULL);
	aux[len] = '\0';
	len--;
	while (n % 10)
	{
		aux[len--] = (n % 10) + '0';
		n /= 10;
	}
	return (aux);
}

void	unlink_all(void)
{
	sem_unlink(SEM_NAME_FORKS);
	sem_unlink(SEM_NAME_WRITE);
	sem_unlink(SEM_NAME_FULL);
	sem_unlink(SEM_NAME_DEAD);
	sem_unlink(SEM_NAME_STOP);
}

bool	start_killer_threads(t_args *args)
{
	if (pthread_create(&args->finish_meals_kill, NULL,
			&ft_finish_meals_kill, args) != 0)
		return (error_failure(STR_ERR_THREAD, NULL, args));
	if (pthread_create(&args->first_die_kill, NULL,
			&ft_first_die_kill, args) != 0)
		return (error_failure(STR_ERR_THREAD, NULL, args));
	return (true);
}
