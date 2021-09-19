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
	int 			num_to_eat;
	uint64_t 		last_meal;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t *left_fork;
	struct s_all	*ptable;
}				t_list;

typedef struct	s_all
{
	int 				philo_num;
	int 				num_to_eat;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	uint64_t			start_time;
	t_list				*philos;
	pthread_mutex_t		*pfork;
	pthread_mutex_t		message;
	pthread_mutex_t 	sleep;
	pthread_mutex_t 	death;
}				t_all;


int					main(int argc, char **argv);
int					ft_atoi(const char *str);
int					ft_isdigit(int s);
int					eating(t_list *philo, unsigned long long sec);
void				sleeping(t_list *philo, unsigned long long sec);
void				thinking(t_list *philo, unsigned long long longsec);
t_all				*philo_init(char **argv);
void				*life(void *arg);
unsigned long long	get_time(void);

#endif