/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvoicu <flvoicu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:59:25 by flvoicu           #+#    #+#             */
/*   Updated: 2025/03/15 10:16:24 by flvoicu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_aux(t_aux *aux)
{
	int	i;

	i = 0;
	while (i != aux->philo_n)
	{
		if (aux->vars[i].check_mutex)
			pthread_mutex_destroy(&aux->vars[i].fork);
		i++;
	}
	if (aux->vars)
		free(aux->vars);
	if (aux->write_check)
		pthread_mutex_destroy(&aux->write);
	if (aux->track_check)
		pthread_mutex_destroy(&aux->track);
	if (aux->death_check)
		pthread_mutex_destroy(&aux->death);
}

static void	in_philo(t_aux *aux, char **av, int i)
{
	t_philo	*p;

	p = &aux->vars[i].philo;
	p->philo_n = i + 1;
	p->die = ft_atoi(av[2]);
	p->eat = ft_atoi(av[3]);
	p->sleep = ft_atoi(av[4]);
	p->last_eat = 0;
	p->times = -1;
	if (ft_atoi(av[5]))
		p->times = ft_atoi(av[5]);
	p->fork_l = &aux->vars[i].fork;
	if (i == ft_atoi(av[1]) - 1)
		p->fork_r = &aux->vars[0].fork;
	else
		p->fork_r = &aux->vars[i + 1].fork;
	p->dead = &aux->dead;
	p->check = &aux->check;
	p->write = &aux->write;
	p->track = &aux->track;
	p->death = &aux->death;
}

static int	in_mutex(pthread_mutex_t *tmp)
{
	if (pthread_mutex_init(tmp, NULL) != 0)
	{
		printf("Mutex initialization failed\n");
		return (0);
	}
	return (1);
}

static int	in_vars(t_aux *aux)
{
	int	i;

	i = 0;
	while (i < aux->philo_n)
	{
		aux->vars[i].check_mutex = in_mutex(&aux->vars[i].fork);
		if (!aux->vars[i].check_mutex)
			return (0);
		i++;
	}
	aux->write_check = in_mutex(&aux->write);
	if (!aux->write_check)
		return (0);
	aux->track_check = in_mutex(&aux->track);
	if (!aux->track_check)
		return (0);
	aux->death_check = in_mutex(&aux->death);
	if (!aux->death_check)
		return (0);
	return (1);
}

int	init(t_aux *aux, char **av)
{
	int	i;

	aux->philo_n = ft_atoi(av[1]);
	aux->vars = malloc(aux->philo_n * sizeof(t_vars));
	if (!aux->vars)
		return (0);
	aux->check = 1;
	aux->dead = 0;
	if (!in_vars(aux))
		return (0);
	i = 0;
	while (i < aux->philo_n)
		in_philo(aux, av, i++);
	return (1);
}
