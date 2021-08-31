#include "philo.h"

int fork2 = 2;

void	list_init(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->philo_num)
	{
		all->philos[i].ID = i + 1;
		i++;
	}
}

void	mutex_init(t_all *all)
{
	int i;

	i = 0;
	pthread_mutex_init(&all->message, NULL);
	pthread_mutex_init(&all->sleep, NULL);
	pthread_mutex_init(&all->death, NULL);
//	all->pfork = malloc(sizeof(pthread_mutex_t *) * all->philo_num);

//	while (i < all->philo_num)
//	{
//		pthread_mutex_init(&all->philos->pfork, NULL);
//		i++;
//	}
}

t_all *philo_init(char **argv)
{
	t_all *all;

	all = malloc(sizeof(t_all));
	all->philo_num = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		all->num_to_eat = ft_atoi(argv[5]);
	else
		all->num_to_eat = 0;
	all->philos = malloc(sizeof(t_list *) * all->philo_num);
	if (!all->philos)
		exit (1);
	list_init(all);
	mutex_init(all);
	return (all);
}

int eating(t_all *philo, int sec)
{
	(void)philo;
	pthread_mutex_lock(philo->pfork);
	fork2 -= 2;

//	printf("%d philo %d is eating\n", sec, philo.philos->ID);
	fork2 += 2;
	usleep(100000);
	//pthread_mutex_unlock(philo.pfork);
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

void	*life(void *arg)
{
	int	i;
	(void)arg;
	struct timeval current_time;
	t_all philo = *(t_all *)arg;
	i = 0;
	gettimeofday(&current_time, NULL);
//	printf("philo_count %d\n", *philo.philo_count);
//	while (i < philo.num_to_eat)
//	{
		eating(philo, current_time.tv_usec);
//		i++;
//	}
	return (NULL);
}

int main(int argc, char **argv)
{
	int	i;
	t_all *philo;
	void *philo_v;
	i = 0;
	if (argc < 5)
	{
		printf("Error. Not enough arguments\n");
		exit(1);
	}
	philo = philo_init(argv);
	pthread_t th[philo->philo_num];
	philo->pfork = malloc(sizeof(pthread_mutex_t *) * philo->philo_num);
	while (i < (*philo).philo_num)
	{
		pthread_mutex_init(philo->pfork, NULL);
		i++;
	}
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
