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

unsigned long long get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	*life(void *arg)
{
	int					i;
	t_list				philo;
	unsigned long long	current_time;

	philo = *(t_list *)arg;
	i = 0;
	if (philo.ID % 2 != 0)
		usleep(1000);
	while (1)
	{
		if (i == philo.num_to_eat)
			break ;
		current_time = get_time();
		eating(&philo, current_time);
		sleeping(&philo, current_time);
		thinking(&philo, current_time);
		i++;
	}
	return (NULL);
}

int main (int argc, char **argv)
{
	int	i;
	t_all *table;
	t_list *philo;

	i = -1;
	table = NULL;
	if (validation(argc, argv))
		return (1);
	table = philo_init(argv);
	table->pfork = malloc(sizeof(pthread_t) * table->philo_num);
	philo = malloc(sizeof(t_list) * table->philo_num);
	pthread_t th[table->philo_num];
	table->start_time = get_time();
	while (++i < table->philo_num)
		pthread_mutex_init(&table->pfork[i], NULL);
	i = - 1;
	while (++i < table->philo_num)
	{
		philo[i].ID = i + 1;
		philo[i].right_fork = &table->pfork[i];
		philo[i].left_fork = &table->pfork[i + 1];
		philo[i].num_to_eat = table->num_to_eat;
//		philo[i].ptable->start_time = table->start_time;
//		philo[i].table->time_to_die = table->time_to_die;
//		philo[i].table->time_to_eat = table->time_to_eat;
//		philo[i].table->time_to_sleep = table->time_to_sleep;
	}
	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_create(&th[i], NULL, &life, &philo[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread\n");
		i++;
	}
//	while (i < table->philo_num)
//	{
//		if (pthread_detach(th[i]) != 0)
//			return (1);
//		i++;
//	}
}