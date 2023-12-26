/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:36:40 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/26 14:33:37 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	print_msg(char *str, char *aux, int exit_number)
{
	if (!aux)
		printf(str, STR_PROG_NAME);
	else
		printf(str, STR_PROG_NAME, aux);
	return (exit_number);
}

int	error_failure(char *str, char *aux, t_args *args)
{
	if (args != NULL)
		free_args(args);
	return (print_msg(str, aux, 0));
}

void	*error_null(char *str, char *aux, t_args *args)
{
	if (args != NULL)
		free_args(args);
	print_msg(str, aux, EXIT_FAILURE);
	return (NULL);
}

void	child_exit(t_args *args, int exit_code)
{
	sem_post(args->actual_philo->sem_meal);
	pthread_join(args->actual_philo->personal_killer, NULL);
	if (exit_code == CHILD_EXIT_ERROR_SEM)
		print_msg(STR_ERR_SEM, NULL, 0);
	if (exit_code == CHILD_EXIT_ERROR_PTHREAD)
		print_msg(STR_ERR_THREAD, NULL, 0);
	sem_close(args->actual_philo->sem_forks);
	sem_close(args->actual_philo->sem_philo_full);
	sem_close(args->actual_philo->sem_philo_dead);
	sem_close(args->actual_philo->sem_write);
	sem_close(args->actual_philo->sem_meal);
	free_args(args);
	exit(exit_code);
}
