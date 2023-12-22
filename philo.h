/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 09:29:51 by migonzal          #+#    #+#             */
/*   Updated: 2022/07/20 10:28:35 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_args
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meal;
	int				zero_time;
	bool			alive;
	bool			hungry;
	int				satisfied;
	pthread_mutex_t	mutex_life;
	pthread_mutex_t	mutex_satisfacion;
	pthread_mutex_t	mutex_print;
}			t_args;

typedef struct s_philo
{
	int				index;
	pthread_t		thread;
	int				meals;
	int				last_meal;
	bool			hungry;
	pthread_mutex_t	fork;
	struct s_philo	*right;
	struct s_philo	*left;
	struct s_args	*args;
}			t_philo;

/* main */

int		ft_get_timestamp(void);
int		main(int argc, char **argv);
int		ft_main_aux1(int argc, char **argv, t_philo **lst_philo, t_args *args);
int		ft_main_aux2(t_philo *lst_philo, t_args *args);

/*	argumentos	*/
//int	ft_isnumber(char *str);
int		n_argc(int argc, t_args *args);
int		atoi_args(char **argv, t_args *args);
void	rellenote(t_args *args, int *m, char **argv);
/*	listas	*/

t_philo	*ft_lstlast(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lstnew(int index);
void	ft_link_list(t_philo *lst_philo);

/*	magic */

void	ft_print(char *msg, t_philo *philo);
void	ft_keep_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);
int		ft_eating(t_philo *philo);
void	*ft_routine(void *philo);

/* Check */

int		ft_check_satisfaction(t_philo *philo, t_args *args);
void	ft_check_status(t_philo *philo, t_args *args);

/* Funciones de los philos */

//void	ft_free_list(t_philo **lst_philo);
void	ft_free_philos(t_philo *lst_philo, t_args *args);
int		ft_create_philos(t_philo **lst_philo, t_args *args);
void	init_philos(t_philo *lst_philo, t_args *args);

/* Funciones de los threads */

int		ft_create_threads(t_philo *lst_philo, void *routine);
int		ft_join_threads(t_philo *lst_philo, t_args *args);
int		ft_create_mutex(t_philo *lst_philo, t_args *args);
int		ft_destroy_mutex(t_philo *lst_philo, t_args *args);	

/* Atoi bien fresquito */

int		ft_atoi(const char *str);

#endif
