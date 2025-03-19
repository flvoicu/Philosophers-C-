/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvoicu <flvoicu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:59:25 by flvoicu           #+#    #+#             */
/*   Updated: 2025/03/19 17:30:58 by flvoicu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	atoi_error(char *s, t_aux *aux)
{
	if (*s != '\0')
	{
		free_aux(aux);
		printf("Invalid number \n");
		exit (1);
	}
}

long	ft_atoi(char *str, t_aux *aux)
{
	int			neg;
	long		val;
	char		*s;

	neg = 1;
	val = 0;
	s = str;
	if (!s)
		return (val);
	while (*s == ' ' || (*str >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			neg = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		val = val * 10 + *s - '0';
		s++;
	}
	atoi_error(s, aux);
	val *= neg;
	return (val);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((size_t)(time.tv_sec * 1000) + \
	(time.tv_usec / 1000));
}

void	real_sleep(size_t time)
{
	size_t	begin;

	begin = get_time();
	while (get_time() - begin < time)
		usleep(100);
}

size_t	write_message(char *message, t_philo *philo)
{
	size_t	time;

	time = get_time();
	pthread_mutex_lock(philo->write);
	printf("%zu %d %s\n", time - philo->init_time, philo->philo_n, message);
	pthread_mutex_unlock(philo->write);
	return (time);
}
