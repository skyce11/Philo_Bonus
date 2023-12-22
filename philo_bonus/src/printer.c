/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:00:40 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/22 14:47:45 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo_bonus.h"


void	print_status(t_philo *philo, char *str)
{
	printf("%d %d %s\n", ft_get_timestamp() - philo->args->zero_time,
		philo->index + 1, str);
}

void print_general_status(t_philo *philo, bool killer, t_status status)
{
	sem_wait(philo->sem_write);
	if (status == DIED)
		print_status(philo, "died");
	else if (status == EATING)
		print_status(philo, "is eating");
	else if (status == SLEEPING)
		print_status(philo, "is sleeping");
	else if (status == THINKING)
		print_status(philo, "is thinking");
	else if (status == FORK_1 || status == FORK_2)
		print_status(philo, "has taken a fork");
	if (!killer)
		sem_post(philo->sem_write);
}