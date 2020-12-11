/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 23:32:34 by larosale          #+#    #+#             */
/*   Updated: 2020/12/11 20:28:32 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*g_forks;
pthread_mutex_t g_write_lock;

/*
** Worker function for the philosopher thread.
** First, it creates a monitoring thread to check for starvation and report
** death.
** Then it starts the working loop of changing the philosopher's states.
*/

static void	*philo_worker(void *ptr)
{
	t_philos	*phil;
	pthread_t	monitor;

	phil = (t_philos *)ptr;
	if (pthread_create(&monitor, NULL, philo_monitor, phil))
		return (NULL);
	if (pthread_detach(monitor))
		return (NULL);
	while (1)
	{
		philo_take_forks(phil);
		philo_eat(phil);
		philo_sleep(phil);
		philo_think(phil);
	}
	return (NULL);
}

/*
** Runs all philosophers' threads (as detached).
*/

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

/*
** Validates the command-line arguments and fills the "par"
** structure with values.
*/

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

/*
** Main function of philo_one.
** Checks command-line arguments, then creates data structures for
** threads (philosophers) and resource mutexes (forks).
** Runs philosophers' threads and starts monitor to detect
** deaths from starvation and reaching maximum eats limit.
** Finally, it cleans up the state (frees memory, destoys mutexes).
*/

int			main(int argc, char **argv)
{
	t_params	*params;
	t_philos	*philos;

	params = NULL;
	philos = NULL;
	if (check_args(argc, argv, &params)
		|| !(philos = create_philos(params))
		|| create_forks(params))
		return (1);
	if (pthread_mutex_init(&g_write_lock, NULL)
		|| get_time(params) < 0)
		return (cleanup(philos, params, ERR_SYS));
	if (run_threads(philos, params))
		return (1);
	monitor_threads(philos, params);
	cleanup(philos, params, OK);
	return (0);
}
