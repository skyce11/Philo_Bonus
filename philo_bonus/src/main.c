/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:52:50 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/22 14:31:12 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../philo_bonus.h"

int	ft_get_timestamp(void)
{
	int				res;
	struct timeval	time;

	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}

void philo_sleep(int t_sleep)
{
	int wake_up;

	wake_up = ft_get_timestamp() + t_sleep;
	while (ft_get_timestamp() < wake_up)
	{
		usleep(100);
	}
}

int get_child_exit_die(t_args *args, pid_t *pid)
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
			if (exit_code == CHILD_EXIT_ERROR_PTHREAD ||
				exit_code  == CHILD_EXIT_ERROR_SEM)
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

bool start_run(t_args *args)
{
	int i;
	pid_t pid;
	args->zero_time = ft_get_timestamp();
	i = -1;
	while (++i < args->n_philo)
	{
		pid = fork();
		if (pid == -1)
			return (error_failure("%s error: Could not fork child.\n", NULL, args));
		else if (pid > 0)
			args->pids[i] = pid;
		else if (pid == 0)
		{
			args->actual_philo = args->philos[i];
			//philo routine
		}
	}
	if (start_killer_threads(args) == false)
		return (false);
	return (true);
}

int stop_run(t_args *args)
{
	int i;
	int exit_code;

	//delay
	
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

bool run_stopped(t_args *args)
{
	bool aux;

	sem_wait(args->sem_stop);
	aux = args->stop_run;
	sem_post(args->sem_stop);
	return (aux);
}

int main(int argc, char **argv)
{
  t_args *args;

  args = NULL;
  if (n_argc(argc, args))
    return (2);
  // revisar mas mierda
  args = init_args(argc, argv, 1);
  if (!args)
	return (EXIT_FAILURE);
if (!start_run(args))
	return (EXIT_FAILURE);
if (stop_run(args) == -1)
	return (args_cleaner(args, EXIT_FAILURE));
return (args_cleaner(args, EXIT_SUCCESS));



}
