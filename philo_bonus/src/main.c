/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:52:50 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/26 12:51:03 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo_bonus.h"



bool run_stopped(t_args *args)
{
	bool aux;

	sem_wait(args->sem_stop);
	aux = args->stop_run;
	sem_post(args->sem_stop);
	return (aux);
}

static bool start_run(t_args *args)
{
	unsigned int i;
	pid_t pid;

	args->zero_time = ft_get_timestamp(); /*+ ((args->n_philo * 2) * 10);*/
	i = -1;
	while (++i < args->n_philo)
	{
		pid = fork();
		if (pid == -1)
			return (error_failure(STR_ERR_FORK, NULL, args));
		else if (pid > 0)
			args->pids[i] = pid;
		else if (pid == 0)
		{
			args->actual_philo = args->philos[i];
			start_routine(args);
		}
	}
	if (start_killer_threads(args) == false)
		return (false);
	return (true);
}




static int get_child_exit_die(t_args *args, pid_t *pid)
{
	int philo_exit_code;
	int exit_code;

	if (*pid && waitpid(*pid, &philo_exit_code, WNOHANG) != 0)
	{
		if (WIFEXITED(philo_exit_code))
		{
			exit_code = WEXITSTATUS(philo_exit_code);
			if (exit_code == CHILD_EXIT_PHILO_DEAD)
				return (kill_philos(args, 1));
			if (exit_code == CHILD_EXIT_ERROR_PTHREAD
			 	|| exit_code  == CHILD_EXIT_ERROR_SEM)
				return (kill_philos(args, -1));
			if (exit_code == CHILD_EXIT_PHILO_FULL)
			{
				args->philo_full_count +=1;
				return (1);
			}
		}
	}
	return (0);
}



static int stop_run(t_args *args)
{
	unsigned int i;
	int exit_code;

	run_start_delay(args->zero_time);
	
	while(run_stopped(args) == false)
	{
		i = 0;
		while(i < args->n_philo)
		{
			exit_code = get_child_exit_die(args, &args->pids[i]);
			if (exit_code == 1 || exit_code == -1)
			{
				sem_wait(args->sem_stop);
				args->stop_run = true;
				sem_post(args->sem_philo_full);
				sem_post(args->sem_philo_dead);
				sem_post(args->sem_stop);
				return (exit_code);
			}
			i++;
		}
	}
	return (0);
}


int main(int argc, char **argv)
{
  t_args *args;

  args = NULL;
  if (argc -1  < 4 || argc -1 > 5)
	return (print_msg(STR_USAGE, NULL, EXIT_FAILURE));
  if (!is_valid_input(argc, argv))
	return (EXIT_FAILURE);
  args = init_args(argc, argv, 1);
  if (!args)
	return (EXIT_FAILURE);
if (!start_run(args))
	return (EXIT_FAILURE);
if (stop_run(args) == -1)
	return (args_cleaner(args, EXIT_FAILURE));
return (args_cleaner(args, EXIT_SUCCESS));



}
