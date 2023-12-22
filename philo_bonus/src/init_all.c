#include "../philo_bonus.h"


int init_semaphores(t_args *)
{
    // Función para hacer unlink
    args->sem_forks = sem_open(SEM_NAME_FORKS, O_CREAT,
                                s_IRUSR | S_IWUSR, args->n_philo);
    if (table->sem_forks == SEM_FAILED)
        return (NULL // Funcioner de error
    table->sem_write = sem_open(SEM_NAME_WRITE, O_CREAT,
                                s_IRUSR | S_IWUSR, 1);
    if (table->)
}


t_args *init_args(int argc, char **argv, int i)
{
t_args *args;

args = malloc(sizeof(t_args) *1);
if (!args)
    return (NULL); // Funcion de error aqui


args->n_philo = ft_atoi(argv[i++]);
args->t_die = ft_atoi(argv[i++]);
args->t_eat = ft_atoi(argv[i++]);
args->t_sleep = ft_atoi(argv[i++]);
if (argc == 6)
    n_meal = ft_atoi(argv[i]);
else
    n_meal = -1;
if (!)
}
