/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:55:31 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/22 14:17:31 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"



void ft_routine(t_philo *philo)
{
	if (philo->index % 2)
		think_routine(philo, true);
	while (1)
	{
		eat_sleep_routine(philo);
		think_routine(philo, false);
	}
}





void pick_fork(t_philo *philo)
{
	sem_wait(philo->sem_forks);
	sem_wait(philo->sem_meal);
	if (philo->forks_picked <= 0)
		print_general_status(philo, false, FORK_1);
	if (philo->forks_picked == 1)
		print_general_status(philo, false, FORK_2);
	philo->forks_picked += 1;
	sem_post(philo->sem_meal);
}

void start_routine(t_args *args)
{
	t_philo *philo;

	philo = args->actual_philo;
	if (philo->args->n_philo == 1)
		only_one_philo(philo);
	open_semaphores(args, philo);
	if (philo->args->n_meal == 0)
	{
		sem_post(philo->sem_philo_full);
		child_exit(args, CHILD_EXIT_PHILO_FULL);
	}
	if (philo->args->t_die == 0)
	{
		sem_post(philo->sem_philo_dead);
		child_exit(args, CHILD_EXIT_PHILO_FULL);
	}
	sem_wait(philo->sem_meal);
	philo->last_meal = philo->args->zero_time;
	sem_post(philo->sem_meal);
	run_start_delay(philo->args->zero_time);
	ft_routine(philo);
}


void eat_sleep_routine(t_philo *philo)
{
	pick_fork(philo);
	pick_fork(philo);
	print_general_status(philo, false, EATING);
	sem_wait(philo->sem_meal);
	philo->last_meal = ft_get_timestamp();
	sem_post(philo->sem_meal);
	philo_sleep(philo->args->t_eat);
	print_general_status(philo, false, SLEEPING);
	sem_post(philo->sem_forks);
	sem_post(philo->sem_forks);
	sem_wait(philo->sem_meal);
	philo->forks_picked -= 2;
	philo->times_eat += 1;
	sem_post(philo->sem_meal);
	philo_sleep(philo->args-> t_sleep);
}

void think_routine(t_philo *philo, bool silent)
{
	printf("Entro aqui alguna vez\n");
	time_t time_to_think;

	sem_wait(philo->sem_meal);
	time_to_think = (philo->args->t_die - (ft_get_timestamp()
		- philo->last_meal) - philo->args->t_eat) / 2;
	sem_post(philo->sem_meal);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		print_general_status(philo, false, THINKING);
	philo_sleep(time_to_think);
}


void only_one_philo(t_philo *philo)
{
	philo->sem_philo_full = sem_open(SEM_NAME_FULL, O_CREAT,
					S_IRUSR | S_IWUSR, philo->args->n_philo);
	if (philo->sem_philo_full == SEM_FAILED)
		exit(CHILD_EXIT_ERROR_SEM);
	sem_wait(philo->sem_philo_full);
	run_start_delay(philo->args->zero_time);
	if (philo->args->n_meal == 0)
	{
		sem_post(philo->sem_philo_full);
		exit(CHILD_EXIT_ERROR_SEM);
	}
	print_status(philo, "has taken a fork");
	philo_sleep(philo->args->t_die);
	print_status(philo, "died");
	free(philo->args);
	exit(CHILD_EXIT_PHILO_DEAD);
}







