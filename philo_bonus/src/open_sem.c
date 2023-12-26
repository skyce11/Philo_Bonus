/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:24:19 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/26 14:46:07 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

bool	open_global_semaphores(t_philo *philo)
{
	philo->sem_forks = sem_open(SEM_NAME_FORKS, O_CREAT,
			S_IRUSR | S_IWUSR, philo->args->n_philo);
	if (philo->sem_forks == SEM_FAILED)
		return (false);
	philo->sem_write = sem_open(SEM_NAME_WRITE, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (philo->sem_write == SEM_FAILED)
		return (false);
	philo->sem_philo_full = sem_open(SEM_NAME_DEAD, O_CREAT,
			S_IRUSR | S_IWUSR, philo->args->n_philo);
	if (philo->sem_philo_full == SEM_FAILED)
		return (false);
	philo->sem_philo_dead = sem_open(SEM_NAME_DEAD, O_CREAT,
			S_IRUSR | S_IWUSR, philo->args->n_philo);
	if (philo->sem_philo_dead == SEM_FAILED)
		return (false);
	return (true);
}

bool	open_local_semaphores(t_philo *philo)
{
	philo->sem_meal = sem_open(philo->sem_meal_name, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (philo->sem_meal == SEM_FAILED)
		return (false);
	sem_unlink(philo->sem_meal_name);
	return (true);
}

void	open_semaphores(t_args *args, t_philo *philo)
{
	if (args->n_philo == 1)
		return ;
	sem_unlink(philo->sem_meal_name);
	if (!open_global_semaphores(philo))
		child_exit(args, CHILD_EXIT_ERROR_SEM);
	if (!open_local_semaphores(philo))
		child_exit(args, CHILD_EXIT_ERROR_SEM);
	if (pthread_create(&philo->personal_killer, NULL,
			&killler, args) != 0)
		child_exit(args, CHILD_EXIT_ERROR_PTHREAD);
	return ;
}
