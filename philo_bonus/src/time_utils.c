# include "../philo_bonus.h"

void run_start_delay(int zero_time)
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
	//printf("Valor de ft_get_timestamp: %ld\n", ft_get_timestamp());
	while (ft_get_timestamp() < wake_up)
	{
		usleep(100);
	}
}
