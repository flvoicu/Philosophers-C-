/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvoicu <flvoicu@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:02:35 by flvoicu           #+#    #+#             */
/*   Updated: 2024/05/15 17:16:01 by flvoicu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					philo_n;
	long long			*last_eat;
	long long			die;
	long long			eat;
	long long			sleep;
	int					*times;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		write;
	int					*check;
}				t_philo;

typedef struct s_vars
{
	char				**av;
	pthread_mutex_t		*fork;
	long long			*eat;
	pthread_mutex_t 	write;
	pthread_t			*thread;
	t_philo				*philo;
	int					*check;
	int					*times;
}				t_vars;

#endif

