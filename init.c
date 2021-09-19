#include "philo.h"

t_list	*list_init(t_all *all, t_list *philos)
{
	int	i;

	i = 0;
	while (i < all->philo_num)
	{
		philos[i].ID = i + 1;
		philos[i].right_fork = &all->pfork[i];
		philos[i].left_fork = &all->pfork[i + 1];
		philos[i].num_to_eat = all->num_to_eat;
//		pthread_mutex_init(philos[i].left_fork, NULL);
//		pthread_mutex_init(philos[i].right_fork, NULL);
//		printf("fg: %d\n", philos[i].ID);
		i++;
	}
	return (philos);
}

void	mutex_init(t_all *all)
{
	pthread_mutex_init(&all->message, NULL);
	pthread_mutex_init(&all->sleep, NULL);
	pthread_mutex_init(&all->death, NULL);
}

t_all *philo_init(char **argv)
{
	t_all *all;
	int i;

	i = 0;
	all = malloc(sizeof(t_all));
	all->philo_num = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		all->num_to_eat = ft_atoi(argv[5]);
	else
		all->num_to_eat = 0;
//	all->pfork = malloc(sizeof(pthread_mutex_t) * all->philo_num);
//	while (i < all->philo_num)
//	{
//		pthread_mutex_init(&all->pfork[i], NULL);
//		i++;
//	}
//	all->philos = malloc(sizeof(t_list) * all->philo_num + 1);
//	if (!all->philos)
//		exit (1);
//	all->philos = list_init(all, all->philos);
//	mutex_init(all);
	return (all);
}
