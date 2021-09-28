#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>


typedef struct	s_list
{
	int				ID;
	int				eat_times;
	uint64_t 		last_meal;
	pthread_t		thread_ID;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t *left_fork;
}				t_list;

typedef struct	s_tab
{
	int 				philo_num;
	int 				num_to_eat;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	uint64_t			start_time;
	pthread_mutex_t		*pfork;
	pthread_mutex_t		message;
	pthread_mutex_t 	sleep;
}				t_tab;

typedef struct s_all
{
	t_tab	*table;
	t_list	*philo;
}				t_all;

int	ft_atoi(const char *str);
void	ft_putnbr(int n);
void	ft_putstr(char *s);
void	ft_putchar(char c);



#endif