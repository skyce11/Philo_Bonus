/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:39:53 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/26 16:33:39 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>



# define MAX_PHILOS 200
# define STR_MAX_PHILOS "200"

# define STR_PROG_NAME "philos:"
# define STR_USAGE "%s usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"

# define STR_ERR_INPUT_DIGIT "%s invalid input: %s: \
not a valid unsigned integer between 0 and 2147483647.\n"

# define STR_ERR_INPUT_POFLOW "%s invalid input: \
there must be between 1 and %s philosophers.\n"

# define STR_ERR_THREAD "%s error: Could not create thread.\n"
# define STR_ERR_MALLOC "%s error: Could not allocate memory.\n"
# define STR_ERR_SEM "%s error: Could not create semaphore.\n"
# define STR_ERR_FORK "%s error: Could not fork child.\n"

# define SEM_NAME_FORKS "/philo_global_forks"
# define SEM_NAME_WRITE "/philo_global_write"
# define SEM_NAME_FULL  "/philo_global_full"
# define SEM_NAME_DEAD  "/philo_global_dead"
# define SEM_NAME_STOP  "/philo_global_stop"
# define SEM_NAME_MEAL "/philo_local_meal_"

# define CHILD_EXIT_ERROR_PTHREAD 40
# define CHILD_EXIT_ERROR_SEM 41
# define CHILD_EXIT_PHILO_FULL 42
# define CHILD_EXIT_PHILO_DEAD 43

typedef struct s_philo	t_philo;


typedef struct s_args
{
	time_t					zero_time;
	unsigned int			n_philo;
	time_t					t_die;
	time_t					t_eat;
	time_t					t_sleep;
	int						n_meal;
	sem_t					*sem_forks;
	sem_t					*sem_write;
	sem_t					*sem_philo_full;
	unsigned int			philo_full_count;
	sem_t					*sem_philo_dead;
	sem_t					*sem_stop;
	bool					stop_run;
	t_philo					*actual_philo;
	t_philo					**philos;
	pid_t					*pids;
	pthread_t				finish_meals_kill;
	pthread_t				first_die_kill;
}	t_args;

typedef struct s_philo
{
	pthread_t		personal_killer;
	sem_t			*sem_forks;
	sem_t			*sem_write;
	sem_t			*sem_philo_full;
	sem_t			*sem_philo_dead;
	sem_t			*sem_meal;
	char			*sem_meal_name;
	unsigned int	forks_picked;
	unsigned int	index;
	unsigned int	times_eat;
	bool			satisfied;
	time_t			last_meal;
	t_args			*args;
}		t_philo;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	FORK_1 = 4,
	FORK_2 = 5,
}	t_status;

//PHILO_UTILS

char *ft_strcat(char *dst, const char *src);
size_t ft_strlen(const char *str);
char *ft_utoa(unsigned int n, size_t len);
void unlink_all(void);
bool start_killer_threads(t_args *args);
void print_sem_value(sem_t *sem);

//INIT_ALLL
char 	*set_meal_name(const char*str, int index);
bool set_philo_meal_name(t_philo *philo);
//t_philo		**init_philos(t_args *args);
bool init_semaphores(t_args *args);
t_args *init_args(int argc, char **argv, int i);

// FT_ARGS
bool only_digits(char *str);
int	integer_atoi(char *str);
bool is_valid_input(int argc, char **argv);




// FT_ERROR
int print_msg(char *str, char *aux, int exit_number);
void *error_null(char *str, char *aux, t_args *args);
int error_failure(char *str, char *aux, t_args *args);
void *free_args(t_args *args);
void child_exit(t_args *args, int exit_code);
int args_cleaner(t_args *args, int exit_code);
int sem_error_cleaner(t_args *args);

//CLEANER
void *free_args(t_args *args);
int sem_error_cleaner(t_args *args);
int args_cleaner(t_args *args, int exit_code);


//MAIN

bool run_stopped(t_args *args);




//PRINTER
void	print_status(t_philo *philo, char *str);
void 	print_general_status(t_philo *philo, bool killer, t_status status);

// FT_KILL.C
int kill_philos(t_args *args, int exit_code);
void *ft_first_die_kill(void *aux);
void *ft_finish_meals_kill(void *aux);
//bool kill_trigger(t_args  *args, t_philo *philo);
void *killler(void *aux);

//ft_routine.c
//void ft_routine(t_philo *philo);
void pick_fork(t_philo *philo);
void start_routine(t_args *args);
//void eat_sleep_routine(t_philo *philo);
//void think_routine(t_philo *philo, bool silent);
//void only_one_philo(t_philo *philo);

//init_semaphores
bool open_global_semaphores(t_philo *philo);
bool open_local_semaphores(t_philo *philo);
void open_semaphores(t_args *args, t_philo *philo);


// Time_utils

void run_start_delay(time_t zero_time);
time_t	ft_get_timestamp(void);
void philo_sleep(time_t sleep_time);







#endif
