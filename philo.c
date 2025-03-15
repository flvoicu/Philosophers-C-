/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flvoicu <flvoicu@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:59:25 by flvoicu           #+#    #+#             */
/*   Updated: 2024/05/23 18:31:18 by flvoicu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(char *str)
{
	int				neg;
	long long		val;
	char			*s;

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
	val *= neg;
	return (val);
}
long long	get_time ()
{
	struct	timeval current_time;
	long long		time;
	
	gettimeofday(&current_time, NULL);
   	time = (long long)(current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

int	in_mutex(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = ft_atoi(vars->av[1]);
	while (i < j)
	{
		if (pthread_mutex_init(&vars->fork[i], NULL) != 0)
        {
			printf("Mutex initialization failed\n");
        	return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&vars->write, NULL) != 0)
	{
		printf("Mutex initialization failed\n");
		return (0);
	}
	return (1);
}

t_philo	in_philo(t_vars *vars, int i)
{
	t_philo			philo;

	philo.philo_n = i;
	philo.die = ft_atoi(vars->av[2]);
	philo.eat = ft_atoi(vars->av[3]);
	philo.sleep = ft_atoi(vars->av[4]);
	philo.last_eat = &vars->eat[i - 1];
	philo.last_eat[0] = get_time();
	philo.times = &vars->times[i - 1];
	philo.times[0] = -1;
	if (ft_atoi(vars->av[5]))
		philo.times[0] = ft_atoi(vars->av[5]);
	philo.fork_l = &vars->fork[i - 1];
	if (i == ft_atoi(vars->av[1]))
		philo.fork_r = &vars->fork[0];
	else
		philo.fork_r = &vars->fork[i];
	philo.write = vars->write;
	philo.check = vars->check;
	return (philo);
}

int	in_vars(t_vars *vars)
{
	long long	i;

	i = ft_atoi(vars->av[1]);
	vars->philo = malloc(i * sizeof(t_philo));
	if (!vars->philo)
		return (0);
	vars->thread = malloc(i * sizeof(pthread_t));
	if (!vars->thread)
		return (0);
	vars->fork = malloc(i * sizeof(pthread_mutex_t));
	if (!vars->fork)
		return (0);
	vars->times = malloc(i * sizeof(int));
	if (!vars->times)
		return (0);
	vars->eat = malloc(i * sizeof(long long));
	if (!vars->eat)
		return (0);
	vars->check = malloc(sizeof(int));
	if (!vars->check)
		return (0);
	vars->check[0] = 1;
	return (1);
}

long long	write_message(char *message, t_philo *philo)
{
	long long		time;
	
	pthread_mutex_lock(&philo->write);
   	time = get_time();
	if (!philo->check[0])
		printf("%lld %d %s\n", time, philo->philo_n, message);
	pthread_mutex_unlock(&philo->write);
	return (time);
}

void	philo_odd(t_philo *philo)
{
	long long		time;

	while (philo->times[0] != 0 && !philo->check[0])
	{
		pthread_mutex_lock(philo->fork_r);
		write_message("has taken a fork", philo);
		pthread_mutex_lock(philo->fork_l);
		time = write_message("is eating", philo);
		philo->last_eat[0] = time;
		philo->times[0]--;
		usleep(philo->eat * 1000);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		if (philo->check[0])
			break ;
		write_message("is sleeping", philo);
		usleep(philo->sleep * 1000);
		if (philo->check[0])
			break ;
		write_message("is thinking", philo);
	}
}

void	philo_round(t_philo *philo)
{
	long long		time;

	while (philo->times[0] != 0 && !philo->check[0])
	{
		pthread_mutex_lock(philo->fork_l);
		write_message("has taken a fork", philo);
		pthread_mutex_lock(philo->fork_r);
		time = write_message("is eating", philo);
		philo->last_eat[0] = time;
		philo->times[0]--;
		usleep(philo->eat * 1000);
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
		if (philo->check[0])
			break ;
		write_message("is sleeping", philo);
		usleep(philo->sleep * 1000);
		if (philo->check[0])
			break ;
		write_message("is thinking", philo);
	}
}

void	*philo_thread(void *arg) {
    t_philo			*philo;

	philo = (t_philo *)arg;
	while (philo->check[0] == 1)
		usleep(1000);
	if (philo->philo_n % 2 == 0)
		philo_round(philo);
	else
		philo_odd(philo);
	return (NULL);
}

void	check_philo(t_vars *vars)
{
	int				i;
	int				num;
	t_philo			philo;
	long long		time;

	num = ft_atoi(vars->av[1]);
	i = 0;
	while(!vars->check[0])
	{
		philo = vars->philo[i];
		time = get_time();
		if (time > philo.die + philo.last_eat[0])
		{
			write_message("died", &philo);
			printf("%lld %lld %lld %lld\n", time, philo.die, philo.last_eat[0], time - philo.last_eat[0]);
			vars->check[0] = 1;
		}
		if (++i == num)
			i = 0;
	}
}

void	*count_times(void *arg)
{
	t_vars	*vars;
	int		i;
	int		j;
	int		tmp;

	vars = (t_vars *)arg;
	i = ft_atoi(vars->av[1]);
	j = 0;
	tmp = 1;
	while (vars->check[0] == 1)
		usleep(1000);
	while (!vars->check[0] && vars->times[0] != -1)
	{
		tmp += vars->times[j];
		if (++j == i)
		{
			if (tmp == 0)
				vars->check[0] = 1;
			j = 0;
			tmp = 0;
		}
	}
	return (NULL);
}

void	manage_thread(t_vars *vars)
{
	int			i;
	
	i = -1;
	while (++i < ft_atoi(vars->av[1]))
	{
		vars->philo[i] = in_philo(vars, i + 1);
		pthread_create(&vars->thread[i], NULL, philo_thread, (void *)&vars->philo[i]);
	}
	pthread_create(&vars->thread[i - 1], NULL, count_times, (void *)vars);
	while ((vars->philo[i - 1]).last_eat[0] == 0)
		usleep(1000);
	vars->check[0] = 0;
	check_philo(vars);
}

int	main (int ac, char *av[])
{
	t_vars	vars;

	if (ac > 6 || ac < 5)
		return (0);
	vars.av = av;
	if (!in_vars(&vars) || !in_mutex(&vars))
		return (1);
	manage_thread(&vars);
	return (0);
}
