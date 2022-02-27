/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelena <ddelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:27:23 by ddelena           #+#    #+#             */
/*   Updated: 2021/11/06 17:40:05 by ddelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_list
{
	int				id;
	int				dead;
	int				eat_times;
	uint64_t		last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}				t_list;

typedef struct s_tab
{
	int					philo_num;
	int					num_to_eat;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	uint64_t			start_time;
	pthread_mutex_t		*pfork;
	pthread_mutex_t		message;
	pthread_mutex_t		sleep;
}				t_tab;

typedef struct s_all
{
	t_tab	*table;
	t_list	*philo;
	int		philo_count;
}				t_all;

int					ft_atoi(const char *str);
void				ft_putnbr(unsigned long long n);
void				ft_putstr(char *s);
size_t				ft_strlen(const char *str);
void				ft_putchar(char c);
int					ft_strncmp(const char *s1, const char *s2);
void				ft_putchar(char c);

//initialization
int					mutex_init(t_tab *table);
void				philo_init(t_all *all);
int					philo_alloc(t_all *all);
int					argv_parsing(t_tab *table, char **argv);

//actions
void				message(t_all *all, t_list *philo, char *msg);
void				waiting(unsigned long long time);
void				eating(t_all *all, t_list *philo);
void				error(char *msg);
unsigned long long	get_time(void);
#endif