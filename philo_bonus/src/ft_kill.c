/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:37:23 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/26 17:57:37 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	kill_philos(t_args *args, int exit_code)
{
	unsigned int	i;

	i = 0;
	while (i < args->n_philo)
	{
		kill(args->pids[i], SIGKILL);
		i++;
	}
	return (exit_code);
}

void	*ft_finish_meals_kill(void *aux)
{
	t_args	*args;

	args = (t_args *) aux;
	if (args->n_meal < 0 || args->t_die == 0
		|| args->n_philo == 1)
		return (NULL);
	run_start_delay(args->zero_time);
	while (args->philo_full_count < args->n_philo)
	{
		if (run_stopped(args) == true)
			return (NULL);
		sem_wait(args->sem_philo_full);
		if (run_stopped(args) == false)
		{
			//printf("Valor de times_eat %d\n", args->actual_philo->times_eat);
			args->philo_full_count += 1;
		}
		else
			return (NULL);
	}
	sem_wait(args->sem_stop);
	args->stop_run = true;
	printf("Eres tu perro\n");
	kill_philos(args, EXIT_SUCCESS);
	sem_post(args->sem_philo_dead);
	sem_post(args->sem_stop);
	return (NULL);
}

void	*ft_first_die_kill(void *aux)
{
	t_args	*args;

	args = (t_args *) aux;
	if (args->n_philo == 1)
		return (NULL);
	run_start_delay(args->zero_time);
	if (run_stopped(args) == true)
		return (NULL);
	sem_wait(args->sem_philo_dead);
	if (run_stopped(args) == true)
		return (NULL);
	sem_wait(args->sem_stop);
	args->stop_run = true;
	kill_philos(args, EXIT_SUCCESS);
	sem_post(args->sem_philo_full);
	sem_post(args->sem_stop);
	return (NULL);
}

static	bool	kill_trigger(t_args *args, t_philo *philo)
{
	sem_wait(philo->sem_meal);
	if (ft_get_timestamp() - philo->last_meal >= args->t_die)
	{
		print_general_status(philo, true, DIED);
		sem_post(args->actual_philo->sem_philo_dead);
		sem_post(philo->sem_meal);
		return (true);
	}
	//printf("Valor de times_eat: %d\n", philo->times_eat);
	if (args->n_meal != -1 && philo->satisfied == false
		&& philo->times_eat >= (unsigned int) args->n_meal)
	{
		sem_post(philo->sem_philo_full);
		philo->satisfied = true;
	}
	sem_post(philo->sem_meal);
	return (false);
}

void	*killler(void *aux)
{
	t_args	*args;

	args = (t_args *)aux;
	 if (args->n_meal == 0)
	 	return (NULL);
	sem_wait(args->actual_philo->sem_philo_dead);
	sem_wait(args->actual_philo->sem_philo_full);
	run_start_delay(args->zero_time);
	while (!kill_trigger(args, args->actual_philo))
	{
		usleep(1000);
		continue ;
	}
	return (NULL);
}
