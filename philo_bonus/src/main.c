/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:52:50 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/21 13:15:36 by migonzal         ###   ########.fr       */
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
	while (ft_get_timestamp < wake_up)
	{
		usleep(100);
	}
}

int main(int argc, char **argv)
{
  t_args *args;

  args = NULL;
  if (n_args(argc, args))
    return (2);
  // revisar mas mierda
  args = 

}
