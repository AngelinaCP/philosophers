#include "philo.h"

int eating(t_list *philo, unsigned long sec)
{
	pthread_mutex_lock(philo->right_fork);
	printf("%lu philo %d has taken a right fork\n", sec, philo->ID);
	printf("%lu philo %d has taken a left fork\n", sec, philo->ID);
	printf("%lu philo %d is eating\n", sec, philo->ID);
	usleep(1000);
	pthread_mutex_unlock(philo->right_fork);
	return (sec);
}

void sleeping(t_list *philo, unsigned long sec)
{
	printf("%lu philo %d is sleeping\n", sec, philo->ID);
}

void thinking(t_list *philo, unsigned long sec)
{
	printf("%lu philo %d is thinking\n", sec, philo->ID);
}
