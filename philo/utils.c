/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelena <ddelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 20:09:52 by ddelena           #+#    #+#             */
/*   Updated: 2021/10/10 20:09:53 by ddelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	long	i;
	int		j;

	i = 0;
	j = 1;
	if (!str)
		return (0);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' )
		j = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (i > 2147483647 && j == 1)
			return (-1);
		if (i < -2147483648)
			return (0);
		i = (*str - 48) + (i * 10);
		str++;
	}
	return (i * j);
}

void	ft_putnbr(unsigned long long n)
{
	if (n == 9223372036854775807)
		ft_putstr("9223372036854775807");
	else if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(n * (-1));
	}
	else if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}

void	ft_putstr(char *s)
{
	if (s)
	{
		while (*s)
		{
			write(1, s, 1);
			s++;
		}
	}
}
