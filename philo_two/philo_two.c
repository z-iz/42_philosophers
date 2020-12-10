/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 23:32:34 by larosale          #+#    #+#             */
/*   Updated: 2020/12/10 17:56:35 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t		*g_forks;
sem_t		*g_write_lock;
sem_t		*g_forks_count;
int			g_forks_left;

static void	*philo_worker(void *ptr)
{
	t_philos	*phil;
	pthread_t	monitor;

	phil = (t_philos *)ptr;
	if (pthread_create(&monitor, NULL, philo_monitor, phil))
		return (cleanup(phil, phil->params, ERR_SYS) ? NULL : NULL);
	if (pthread_detach(monitor))
		return (cleanup(phil, phil->params, ERR_SYS) ? NULL : NULL);
	while (1)
	{
		philo_take_forks(phil);
		philo_eat(phil);
		philo_sleep(phil);
		philo_think(phil);
	}
	return (NULL);
}

static int	run_threads(t_philos *philos, t_params *params)
{
	t_philos	*temp;
	int			i;

	temp = philos;
	i = -1;
	while (++i < params->thr_num)
	{
		if (pthread_create(&(temp->thread), NULL, philo_worker, temp))
			return (cleanup(philos, params, ERR_SYS));
		if (pthread_detach(temp->thread))
			return (cleanup(philos, params, ERR_SYS));
		temp++;
	}
	return (0);
}

static int	check_args(int argc, char **argv, t_params **par)
{
	t_params	*params;

	if (!(params = ft_calloc(1, sizeof(t_params))))
		return (cleanup(NULL, params, ERR_SYS));
	if (argc != 5 && argc != 6)
		return (cleanup(NULL, params, ERR_ARGNUM));
	if ((params->thr_num = ft_atoi(*(argv + 1))) < 2)
		return (cleanup(NULL, params, ERR_ARGPHL));
	else if (params->thr_num > MAX_THREADS)
		return (cleanup(NULL, params, ERR_ARGPHH));
	if ((params->t_die = ft_atoi(*(argv + 2))) < MIN_TIME
		|| (params->t_eat = ft_atoi(*(argv + 3))) < MIN_TIME
		|| (params->t_sleep = ft_atoi(*(argv + 4))) < MIN_TIME)
		return (cleanup(NULL, params, ERR_ARGTIM));
	if (argc == 6 && (params->num_eats = ft_atoi(*(argv + 5))) < 1)
		return (cleanup(NULL, params, ERR_ARGEAT));
	*par = params;
	return (0);
}

int			main(int argc, char **argv)
{
	t_params	*params;
	t_philos	*philos;

	params = NULL;
	philos = NULL;
	if (check_args(argc, argv, &params)
		|| !(philos = create_philos(params))
		|| create_sems(params))
		return (1);
	get_time(params);
	g_forks_left = params->thr_num;
	if (run_threads(philos, params))
		return (1);
	monitor_threads(philos, params);
	printf("TEST\n");
	cleanup(philos, params, OK);
	return (0);
}
