/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:36:26 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/22 15:11:28 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../philo_bonus.h"




char 	*set_meal_name(const char*str, int index)
{
	int i;
	int digit_count;
	char *sem_name;
	char *aux;

	digit_count = 0;
	i = index;
	while(i)
	{
		digit_count++;
		i /= 10;
	}
	i = ft_strlen(str) + digit_count;
	sem_name = malloc(sizeof * sem_name * (i +1));
	if (sem_name  == NULL)
		return (NULL);
	sem_name[0] = '\0';
	sem_name = ft_strcat(sem_name, str);
	aux = ft_itoa(index, digit_count);
	sem_name = ft_strcat(sem_name, aux);
	free(aux);
	return (sem_name);
}

bool set_philo_meal_name(t_philo *philo)
{
	philo->sem_meal_name = set_meal_name(SEM_NAME_MEAL, philo->index +1);
	if (philo->sem_meal_name == NULL)
		return (false);
	return (true);
}

t_philo		**init_philos(t_args *args)
{
	t_philo		**philos;
	int 		i;

	philos = malloc(sizeof(t_philo) * (args->n_philo +1));
	if (!philos)
		return (error_null("%s error: Could not allocate memory.\n", NULL, 0)); //FUNCION DE ERROR
	i = 0;
	while (i < args->n_philo)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (error_null("%s error: Could not allocate memory.\n", NULL, 0));
		philos[i]->args = args;
		philos[i]->index = i;
		if (!set_philo_meal_name(philos[i]))
			return (error_null("%s error: Could not allocate memory.\n", NULL, args)); //FUNCION ERROR
		philos[i]->times_eat = 0;
		philos[i]->forks_picked = 0;
		philos[i]->satisfied = false;
		i++;
	}
	return (philos);
}

bool init_semaphores(t_args *args)
{
    unlink_all();
    args->sem_forks = sem_open(SEM_NAME_FORKS, O_CREAT,
                                S_IRUSR | S_IWUSR, args->n_philo);
    if (args->sem_forks == SEM_FAILED)
        return (sem_error_cleaner(args)); // Funcioner de error
    args->sem_write = sem_open(SEM_NAME_WRITE, O_CREAT,
                                S_IRUSR | S_IWUSR, 1);
    if (args->sem_write == SEM_FAILED)
		return (sem_error_cleaner(args)); //FUNCION DE ERROR
	args ->sem_philo_full = sem_open(SEM_NAME_FULL, O_CREAT,
								S_IRUSR | S_IWUSR, args->n_philo);
	if (args->sem_philo_full == SEM_FAILED)
		return (sem_error_cleaner(args)); //FUNCION DE ERROR
	args->sem_philo_dead = sem_open(SEM_NAME_DEAD, O_CREAT,
								S_IRUSR | S_IWUSR, args->n_philo);
	if (args->sem_philo_dead == SEM_FAILED)
		return (sem_error_cleaner(args)); //FUNCION DE ERROR
	args->sem_stop = sem_open(SEM_NAME_STOP, O_CREAT,
								S_IRUSR | S_IWUSR, 1);
	if (args->sem_stop == SEM_FAILED)
		return (sem_error_cleaner(args));
	return (true);
}




t_args *init_args(int argc, char **argv, int i)
{
	t_args *args;

	args = malloc(sizeof(t_args) *1);
	if (!args)
		return (error_null("%s error: Could not allocate memory.\n", NULL, 0)); // Funcion de error aqui


	args->n_philo = ft_atoi(argv[i++]);
	args->t_die = ft_atoi(argv[i++]);
	args->t_eat = ft_atoi(argv[i++]);
	args->t_sleep = ft_atoi(argv[i++]);
	args->philo_full_count = 0;
	args->stop_run = false;
	if (argc == 6)
  		args->n_meal = ft_atoi(argv[i]);
	else
  		args->n_meal = -1;
	if (!init_semaphores(args))
		return (NULL);
	args->philos = init_philos(args);
	if (!args->philos)
		return (NULL);
	args->pids = malloc(sizeof * args->pids * args->n_philo);
	if(!args->pids)
		return (error_null("%s error: Could not allocate memory.\n", NULL, 0)); //FUNCION ERROR
	return (args);

}
