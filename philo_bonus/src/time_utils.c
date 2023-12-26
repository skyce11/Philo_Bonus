/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <migonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:47:58 by migonzal          #+#    #+#             */
/*   Updated: 2023/12/26 16:33:29 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	run_start_delay(time_t zero_time)
{
	while (ft_get_timestamp() < zero_time)
		continue ;
}

time_t	ft_get_timestamp(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_sleep(time_t sleep_time)
{
	time_t	wake_up;

	wake_up = ft_get_timestamp() + sleep_time;
	while (ft_get_timestamp() < wake_up)
	{
		usleep(100);
	}
}
