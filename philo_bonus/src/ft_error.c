/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:36:40 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/22 13:58:13 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo_bonus.h"

int print_msg(char *str, char *aux, int exit_number)
{
	if (!aux)
		printf(str, "philo:");
	else
		printf(str, "philo:", aux);

	return (exit_number);
}

int error_failure(char *str, char *aux, t_args *args)
{
	if (args != NULL)
		free_args(args);
	return (print_msg(str, aux, 0));
}



void *error_null(char *str, char *aux, t_args *args)
{
	if (args != NULL)
		free_args(args);
	print_msg(str, aux, EXIT_FAILURE);
	return (NULL);
}


void *free_args(t_args *args)
{
	int i;

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

void child_exit(t_args *args, int exit_code)
{
	sem_post(args->actual_philo->sem_meal);
	pthread_join(args->actual_philo->personal_killer, NULL);
	if (exit_code == CHILD_EXIT_ERROR_SEM)
		print_msg("%s error: Could not create semaphore.\n", NULL, 0);
	if (exit_code == CHILD_EXIT_ERROR_PTHREAD)
		print_msg("%s error: Could not create thread.\n", NULL, 0);
	sem_close(args->actual_philo->sem_forks);
	sem_close(args->actual_philo->sem_philo_full);
	sem_close(args->actual_philo->sem_philo_dead);
	sem_close(args->actual_philo->sem_write);
	sem_close(args->actual_philo->sem_meal);
	free_args(args);
	exit(exit_code);

}

int sem_error_cleaner(t_args *args)
{
	sem_close(args->sem_forks);
	sem_close(args->sem_write);
	sem_close(args->sem_philo_full);
	sem_close(args->sem_stop);
	unlink_all();
	return (error_failure("%s error: Could not create semaphore.\n", NULL, args));

}

int args_cleaner(t_args *args, int exit_code)
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
	exit(exit_code);
}