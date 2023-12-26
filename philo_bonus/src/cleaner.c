/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:11:25 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/26 14:30:20 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	*free_args(t_args *args)
{
	unsigned int	i;

	if (!args)
		return (NULL);
	if (args->philos != NULL)
	{
		i = 0;
		while (i < args->n_philo)
		{
			if (args->philos[i] != NULL)
			{
				if (args->philos[i]->sem_meal_name)
					free(args->philos[i]->sem_meal_name);
				free(args->philos[i]);
			}
			i++;
		}
		free(args->philos);
	}
	if (args->pids)
		free(args->pids);
	free(args);
	return (NULL);
}

int	sem_error_cleaner(t_args *args)
{
	sem_close(args->sem_forks);
	sem_close(args->sem_write);
	sem_close(args->sem_philo_full);
	sem_close(args->sem_philo_dead);
	sem_close(args->sem_stop);
	unlink_all();
	return (error_failure(STR_ERR_SEM, NULL, args));
}

int	args_cleaner(t_args *args, int exit_code)
{
	if (args != NULL)
	{
		pthread_join(args->first_die_kill, NULL);
		pthread_join(args->finish_meals_kill, NULL);
		sem_close(args->sem_forks);
		sem_close(args->sem_write);
		sem_close(args->sem_philo_full);
		sem_close(args->sem_philo_dead);
		sem_close(args->sem_stop);
		unlink_all();
		free_args(args);
	}
	exit(exit_code);
}
