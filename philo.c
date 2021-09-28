#include "philo.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


void	error(char *msg)
{
	int	i;

	i = ft_strlen(msg);
	write(1, "Error: ", 7);
	write(1, msg, i);
	write(1, "\n", 1);
	exit (1);
}

int	argv_parsing(t_tab *table, char **argv)
{
	table->philo_num = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		table->num_to_eat = ft_atoi(argv[5]);
		if (table->num_to_eat == 0)
			return (1);
	}
	else
		table->num_to_eat = 0;
	if (table->philo_num <= 0 || table->time_to_die <= 0 || table->time_to_eat <= 0 || //
		table->time_to_sleep <= 0)
		return (1);
	return (0);

}

int philo_alloc(t_all *all)
{
	all->table->pfork = malloc(sizeof(all->table->pfork) * all->table->philo_num);
	if (!all->table->pfork)
		return (-1);
	all->philo = malloc(sizeof(all->philo) * all->table->philo_num);
	if (!all->philo)
		return (-1);

	return (0);
}

int	mutex_init(t_tab *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_mutex_init(table->pfork + i, NULL))
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&table->message, NULL))
		return (-1);
	return (0);
}

void	philo_init(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->table->philo_num)
	{
		all->philo[i].ID = i + 1;
		all->philo[i].left_fork = &all->table->pfork[i];
		all->philo[i].right_fork = &all->table->pfork[(i + 1) % all->table->philo_num];
		all->philo[i].eat_times = 0;
		i++;
	}
}

unsigned long long get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	message(t_all *all, t_list *philo, char *msg)
{
	unsigned long long time;

	time = get_time() - all->table->start_time;
	pthread_mutex_lock(&all->table->message);
	//printf("ID: %d\n", philo->ID);
	if (time > 0)
	{
		ft_putnbr(time);
		ft_putchar(' ');
		ft_putnbr(philo->ID);
		ft_putchar(' ');
		ft_putstr(msg);
		ft_putstr("\n");
	}
	pthread_mutex_unlock(&all->table->message);
}

void	eating(t_all *all, t_list *philo)
{
	pthread_mutex_lock(philo->right_fork);
	message(all, philo, "has taken a right fork");
	pthread_mutex_lock(philo->left_fork);
	message(all, philo, "has taken a left fork");
}

void *life(void *cp_all)
{
	t_all *all;


	all = cp_all;
	eating(all, all->philo);
	usleep(50);
	return (NULL);
}

int	create_philo(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->table->philo_num)
	{
		all->table->start_time = get_time();
		if (pthread_create(&all->philo[i].thread_ID, NULL, life, all))
			return (-1);
		usleep(50);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_tab table;
	t_all all;

	all.table = &table;
	if (argc < 5 || argc > 6)
		error("Wrong number of arguments");
	if (argv_parsing(&table, argv))
		error("Wrong argument");
	if (philo_alloc(&all))
		error("Allocation failed");
	if (mutex_init(all.table) == -1)
		error("Mutex initialization failed");
	philo_init(&all);
	if (create_philo(&all))
		error("Failed to create a thread");

}