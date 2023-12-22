/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:39:53 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/21 12:17:51 by migonzal         ###   ########.fr       */
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



typedef struct s_args
{
  int				n_philo;
  int				t_die;
  int				t_eat;
  int				t_sleep;
  int				n_meal;
  int                           zero_time;

  sem_t                         *sem_forks;
  sem_t                         *sem_write;
  sem_t                         *sem_philo_dead;

  t_philo                       **philos;
  t_philo                       *actual_philo;


} t_args;

typedef struct s_philo
{
	int		index;
	int		times_eat;
        int             last_meal;

	int		forks_picked;
        bool            hungry;
	bool	satisfied;
	
        t_args          *args;


	sem_t	*sem_forks;


} 	t_philo;



// FT_ARGS

int n_argc(int argc, t_args *args);

//FT_ATOI
int ft_atoi(const char *str);




#endif
