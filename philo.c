#include "philo.h"

int validation(int argc, char **argv)
{
	(void)argv;
	if (argc < 5)
	{
		printf("Not enough arguments\n");
		return (1);
	}
	return (0);
}

void	*life(void *arg)
{
	int	i;
	struct timeval current_time;
	t_list philo;

	philo = *(t_list *)arg;
	i = 0;
	if (philo.ID % 2 != 0)
		usleep(1000);
	gettimeofday(&current_time, NULL);
	while (i < philo.num_to_eat)
	{
		eating(&philo, current_time.tv_usec);
		sleeping(&philo, current_time.tv_usec);
		thinking(&philo, current_time.tv_usec);
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	int	i;
	t_all *philo;
	void *philo_v;

	if (validation(argc, argv))
		return(1);
	philo = philo_init(argv);
	pthread_t th[philo->philo_num];
	philo->pfork = malloc(sizeof(pthread_mutex_t) * philo->philo_num);
	i = 0;
	while (i < philo->philo_num)
	{
		philo_v = (void *)(&philo->philos[i]);
		if (pthread_create(&th[i], NULL, &life, philo_v) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < philo->philo_num)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread\n");
		i++;
	}
	pthread_mutex_destroy(philo->pfork);
}
