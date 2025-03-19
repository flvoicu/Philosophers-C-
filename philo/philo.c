/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvoicu <flvoicu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:59:25 by flvoicu           #+#    #+#             */
/*   Updated: 2025/03/19 16:41:51 by flvoicu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo(t_aux *aux, int max, int i)
{
	pthread_mutex_lock(&aux->track);
	if (aux->check == max)
	{
		pthread_mutex_unlock(&aux->track);
		return (0);
	}
	pthread_mutex_unlock(&aux->track);
	pthread_mutex_lock(&aux->track);
	if (aux->vars[i].philo.times != 0 && \
	get_time() - aux->vars[i].philo.last_eat >= aux->vars[i].philo.die)
	{
		pthread_mutex_unlock(&aux->track);
		pthread_mutex_lock(&aux->death);
		aux->dead = 1;
		pthread_mutex_unlock(&aux->death);
		write_message("died", &aux->vars[i].philo);
		return (0);
	}
	pthread_mutex_unlock(&aux->track);
	return (1);
}

void	manage_thread(t_aux *aux)
{
	int		i;
	size_t	time;

	i = 0;
	time = get_time();
	while (i < aux->philo_n)
	{
		aux->vars[i].philo.last_eat = time;
		aux->vars[i].philo.init_time = time;
		pthread_create(&aux->vars[i].thread, NULL, \
		philo_thread, (void *)&aux->vars[i].philo);
		i++;
	}
	pthread_mutex_lock(&aux->track);
	aux->check = 0;
	pthread_mutex_unlock(&aux->track);
	while (42)
	{
		i = 0;
		while (i < aux->philo_n)
			if (!check_philo(aux, aux->philo_n, i++))
				return ;
	}
}

int	main(int ac, char *av[])
{
	t_aux	aux;
	int		i;

	if (ac > 6 || ac < 5)
		return (0);
	if (!init(&aux, av))
	{
		free_aux(&aux);
		return (1);
	}
	manage_thread(&aux);
	i = -1;
	while (++i < aux.philo_n && aux.philo_n > 1)
		pthread_join(aux.vars[i].thread, NULL);
	free_aux(&aux);
	return (0);
}
