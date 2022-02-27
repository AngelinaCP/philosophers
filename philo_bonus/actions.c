/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelena <ddelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 20:09:54 by ddelena           #+#    #+#             */
/*   Updated: 2021/10/17 19:30:20 by ddelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	message(t_all *all, t_list *philo, char *msg)
{
	unsigned long long	time;

	time = get_time() - all->table->start_time;
	sem_wait(all->table->message);
	ft_putnbr(time);
	write(1, " ", 1);
	write(1, "philo ", 7);
	ft_putnbr(philo->id + 1);
	write(1, " ", 1);
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	if (ft_strncmp(msg, "has died"))
		sem_post(all->table->message);
}

void	waiting(unsigned long long time)
{
	unsigned long long	start;

	start = get_time();
	while (time > get_time() - start)
		usleep(100);
	return ;
}

void	eating(t_all *all, t_list *philo)
{
	sem_wait(all->table->pfork);
	message(all, philo, "has taken a left fork");
	sem_wait(all->table->pfork);
	message(all, philo, "has taken a right fork");
	message(all, philo, "is eating");
	philo->eat_times++;
	philo->last_meal = get_time();
	waiting(all->table->time_to_eat);
	sem_post(all->table->pfork);
	sem_post(all->table->pfork);
}

void	*life(void *argc)
{
	t_all	*all;

	all = argc;
	all->philo->id = all->philo_count;
	all->philo->last_meal = get_time();
	while (1)
	{
		eating(all, all->philo);
		message(all, all->philo, "is sleeping");
		waiting(all->table->time_to_sleep);
		message(all, all->philo, "is thinking");
	}
	return (NULL);
}
