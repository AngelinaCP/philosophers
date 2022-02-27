/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelena <ddelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 20:09:47 by ddelena           #+#    #+#             */
/*   Updated: 2021/10/17 19:29:42 by ddelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		all->philo[i].id = i + 1;
		all->philo[i].left_fork = &all->table->pfork[i];
		all->philo[i].right_fork = &all->table->pfork[(i + 1) \
			% all->table->philo_num];
		all->philo[i].eat_times = 0;
		all->philo[i].dead = 0;
		i++;
	}
}

int	philo_alloc(t_all *all)
{
	all->table->pfork = malloc(sizeof(*all->table->pfork) \
		* all->table->philo_num);
	if (!all->table->pfork)
		return (-1);
	all->philo = malloc(sizeof(*all->philo) * all->table->philo_num);
	if (!all->philo)
		return (-1);
	return (0);
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
		table->num_to_eat = INT_MAX;
	if (table->philo_num <= 0 || table->time_to_die <= 0 || \
		table->time_to_eat <= 0 || table->time_to_sleep <= 0)
		return (1);
	return (0);
}

void	ft_putchar(char c)
{
	write(1, &c, sizeof(c));
}
