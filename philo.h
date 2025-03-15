/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvoicu <flvoicu@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:02:35 by flvoicu           #+#    #+#             */
/*   Updated: 2025/02/17 18:32:44 by flvoicu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define FIRST 1
# define SECOND 2

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					philo_n;
	size_t				die;
	size_t				eat;
	size_t				sleep;
	size_t				last_eat;
	size_t				init_time;
	int					times;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		*write;
	pthread_mutex_t		*track;
	pthread_mutex_t		*death;
	int					*check;
	int					*dead;
}				t_philo;

typedef struct s_vars
{
	pthread_mutex_t		fork;
	int					check_mutex;
	pthread_t			thread;
	t_philo				philo;
}				t_vars;

typedef struct s_aux
{
	int					philo_n;
	int					check;
	pthread_mutex_t		write;
	int					write_check;
	pthread_mutex_t		track;
	int					track_check;
	pthread_mutex_t		death;
	int					death_check;
	int					dead;
	t_vars				*vars;
}				t_aux;

void	*philo_thread(void *arg);

int		init(t_aux *aux, char **av);
void	free_aux(t_aux *aux);

long	ft_atoi(char *str);
size_t	get_time(void);
void	real_sleep(size_t time);
size_t	write_message(char *message, t_philo *philo);

#endif
