/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvoicu <flvoicu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:59:25 by flvoicu           #+#    #+#             */
/*   Updated: 2025/03/15 11:14:19 by flvoicu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (*(philo->dead))
	{
		pthread_mutex_unlock(philo->death);
		return (0);
	}
	pthread_mutex_unlock(philo->death);
	return (1);
}

int	philo_eat(t_philo *philo, pthread_mutex_t *one, pthread_mutex_t *two)
{
	pthread_mutex_lock(one);
	if (!check_death(philo))
	{
		pthread_mutex_unlock(one);
		return (0);
	}
	write_message("has taken a fork", philo);
	pthread_mutex_lock(two);
	if (!check_death(philo))
	{
		pthread_mutex_unlock(two);
		pthread_mutex_unlock(one);
		return (0);
	}
	pthread_mutex_lock(philo->track);
	philo->last_eat = write_message("is eating", philo);
	philo->times--;
	pthread_mutex_unlock(philo->track);
	real_sleep(philo->eat);
	pthread_mutex_unlock(one);
	pthread_mutex_unlock(two);
	return (1);
}

void	philo_run(t_philo *philo, pthread_mutex_t *one, pthread_mutex_t *two)
{
	while (philo->times != 0)
	{
		if (!philo_eat(philo, one, two))
			return ;
		if (!check_death(philo))
			return ;
		write_message("is sleeping", philo);
		real_sleep(philo->sleep);
		if (!check_death(philo))
			return ;
		write_message("is thinking", philo);
	}
	pthread_mutex_lock(philo->track);
	*(philo->check) += 1;
	pthread_mutex_unlock(philo->track);
}

void	*philo_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->track);
		if (*(philo->check) == 0)
			break ;
		pthread_mutex_unlock(philo->track);
	}
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->track);
	real_sleep(philo->philo_n);
	if (philo->philo_n % 2 == 0)
		philo_run(philo, philo->fork_r, philo->fork_l);
	else
		philo_run(philo, philo->fork_l, philo->fork_r);
	return (NULL);
}
