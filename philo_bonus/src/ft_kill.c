/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:37:23 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/22 13:58:53 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo_bonus.h"



int kill_philos(t_args *args, int exit_code)
{
	int i;
	
	i = 0;
	while(i <args->n_philo)
	{
		kill(args->pids[i], SIGKILL);
		i++;
	}
	return (exit_code);
}

void *first_die_kill(void *aux)
{
	t_args *args;
	
	args = (t_args*) aux;
	if (args->n_philo == 1)
		return (NULL);
	//delay
	if (run_stopped(args) == true)
		return (NULL);
	sem_wait(args->sem_stop);
	args->stop_run = true;
	kill_philos(args, EXIT_SUCCESS);
	sem_post(args->sem_philo_full);
	sem_post(args->sem_stop);
	return (NULL);
}

void *finish_meals_kill(void *aux)
{
	t_args *args;

	args = (t_args*) aux;
	if (args->must_eat_count < 0 || args->t_die == 0
		|| args->n_philo == 1)
		return (NULL);
	// delay
	while (args->philo_full_count < args->n_philo)
	{
		if (run_stopped(args) == true)
			args->philo_full_count += 1;
		else
			return (NULL);
	}
	sem_wait(args->sem_stop);
	args->stop_run = true;
	kill_philos(args, EXIT_SUCCESS);
	sem_post(args->sem_philo_dead);
	sem_post(args->sem_stop);
	return (NULL);
}

bool kill_trigger(t_args  *args, t_philo *philo)
{
	sem_wait(philo->sem_meal);
	if (ft_get_timestamp() - philo->last_meal >= args->t_die)
	{
		print_general_status(philo, true, DIED);
		sem_post(args->actual_philo->sem_philo_dead);
		sem_post(philo->sem_meal);
		return (true);
	}
	if (args->must_eat_count != 1  && philo->satisfied == false
		&& philo->times_eat >= args->must_eat_count)
	{
		sem_post(philo->sem_philo_full);
		philo->satisfied = true;
	}
	sem_post(philo->sem_meal);
	return (false);
}

void *killler(void *aux)
{
	t_args *args;
	args = (t_args*)aux;
	if (args->must_eat_count == 0)
		return (NULL);
	sem_wait(args->actual_philo->sem_philo_dead);
	sem_wait(args->actual_philo->sem_philo_full);
	//delay
	while(!kill_trigger(args, args->actual_philo))
	{
		usleep(1000);
		continue ;
	}
	return (NULL);
}