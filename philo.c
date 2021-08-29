#include "philo.h"

pthread_mutex_t pfork;
int fork2 = 2;
int philo_eating = 0;

t_list *philo_init(char **argv)
{
	t_list *philo;

	philo = malloc(sizeof(t_list));
	philo->philo_count = 0;
	philo->philo_num = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->eating = ft_atoi(argv[3]);
	philo->sleeping = ft_atoi(argv[4]);
	if (argv[5])
		philo->num_to_eat = ft_atoi(argv[5]);
	return (philo);
}

int eating(t_list philo, int sec)
{
	pthread_mutex_lock(&pfork);
	philo_eating++;
	fork2 -= 2;
	printf("%d philo %d is eating\n", sec,* philo.philo_count);
	fork2 += 2;
	usleep(100000);
	pthread_mutex_unlock(&pfork);
	return (sec);
}

void sleeping(int i)
{
	printf("Philo %d is sleeping\n", i);
}

void thinking(int i)
{
	printf("Philo %d is thinking\n", i);
}

void	*doing(void *arg)
{
	int	i;
	struct timeval current_time;
	t_list philo = *(t_list *)arg;

	i = 0;
	gettimeofday(&current_time, NULL);
	printf("philo_count %d\n", *philo.philo_count);
	while (i < philo.num_to_eat)
	{
		eating(philo, current_time.tv_usec);
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	int	i;
	t_list *philo;

	i = 0;
	if (argc < 5)
	{
		printf("Error. Not enough arguments\n");
		exit(1);
	}
	philo = philo_init(argv);
	pthread_t th[philo->philo_num];
	pthread_mutex_init(&pfork, NULL);
	while (i < philo->philo_num)
	{
		philo->philo_count = malloc(sizeof(int));
		*philo->philo_count = i;
		if (i == 1)
		{
			if (pthread_create(&th[i], NULL, &doing, philo) != 0)
				return (1);
		}
		else
		{
			if (pthread_create(&th[i], NULL, &doing, philo) != 0)
				return (1);
		}
		i++;
	}
	i = 0;
	while (i < philo->philo_num)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread\n");
		i++;
	}
	pthread_mutex_destroy(&pfork);
}
