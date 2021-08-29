#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct	s_list
{
	int 			philo_num;
	int 			num_to_eat;
	unsigned long	time_to_die;
	unsigned long	eating;
	unsigned long	sleeping;
	int				*philo_count;
}				t_list;


int main(int argc, char **argv);
int	ft_atoi(const char *str);
int	ft_isdigit(int s);

#endif