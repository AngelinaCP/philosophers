#include "philo.h"

int eating(t_list *philo, unsigned long long sec)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	printf("%llu philo %d has taken a right fork\n", sec, philo->ID);
	printf("%llu philo %d has taken a left fork\n", sec, philo->ID);
	printf("%llu philo %d is eating\n", sec, philo->ID);
	usleep(1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (sec);
}

void sleeping(t_list *philo, unsigned long long sec)
{
	printf("%llu philo %d is sleeping\n", sec, philo->ID);
}

void thinking(t_list *philo, unsigned long long sec)
{
	printf("%llu philo %d is thinking\n", sec, philo->ID);
}
