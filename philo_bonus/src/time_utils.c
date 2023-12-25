# include "../philo_bonus.h"

void run_start_delay(int zero_time)
{
	while (ft_get_timestamp() < zero_time)
		continue ;
}

time_t	ft_get_timestamp(void)
{
	struct timeval tv;

       gettimeofday(&tv, NULL);
       return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));


}


void philo_sleep(int t_sleep)
{
	time_t wake_up;

	wake_up = ft_get_timestamp() + t_sleep;
	while (ft_get_timestamp() < wake_up)
	{
		usleep(100);
	}
}