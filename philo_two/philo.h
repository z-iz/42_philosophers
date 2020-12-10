/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 23:38:20 by larosale          #+#    #+#             */
/*   Updated: 2020/12/10 12:32:01 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

/*
** MAX_THREADS defines maxumum number of threads allowed in the program
** arguments.
** MIN_TIME defines minimum time values allowed in the program arguments.
** CHECK_PERIOD defines interval for the philosopher death monitor.
*/

# define MAX_THREADS	(200)
# define MIN_TIME		(60)
# define CHECK_PERIOD	(1000)

# define LOCK			(1)
# define UNLOCK			(2)

/*
** Global variables used to keep semaphores for forks and writing output.
*/

extern				sem_t *g_forks;
extern				sem_t *g_write_lock;

/*
** Enumeration of philosopher's states.
*/

typedef enum		e_states
{
	THINKING = 1,
	TAKEN_FORK,
	TAKEN_FORKS,
	EATING,
	SLEEPING,
	ATE,
	DIED
}					t_states;

/*
** The structure of type "t_params" defines parameters, obtained through the
** program arguments:
** - number of threads (philosophers, forks);
** - times to die, eat, sleep;
** - number of maximum eats;
** Also, it contains the program starting time.
*/

typedef struct		s_params
{
	int				thr_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eats;
	long			start_time;
}					t_params;

/*
** The structure of type "t_philos" defines philosopher's parameters:
** - number, starting from 1;
** - associated thread variable;
** - state (starts with THINKING);
** - number of times the philosopher ate;
** - time of last eat (from its start);
** - semaphore for locking the state;
** - pointer to params structure.
*/

typedef struct		s_philos
{
	int				num;
	pthread_t		thread;
	t_states		state;
	int				num_ate;
	int				last_eat;
	sem_t*			state_lock;
	t_params		*params;
}					t_philos;

/*
** Philosophers - initialization
*/

t_philos			*create_philos(t_params *params);
int					create_sems(t_params *params);

/*
** Philosophers - actions
*/

void				philo_think(t_philos *phil);
void				philo_take_forks(t_philos *phil);
void				philo_eat(t_philos *phil);
void				philo_sleep(t_philos *phil);

/*
** Philosophers - monitors
*/

void				*philo_monitor(void *ptr);
void				monitor_threads(t_philos *philos, t_params *params);

/*
** Philosophers - utilites
*/

void				print_status(int num, t_states state, int time);
int					get_time(t_params *params);
int					cleanup(t_philos *phil, t_params *params, int errnum);

/*
** Common utils
*/

int					ft_atoi(const char *str);
size_t				ft_strlen(char *str);
void				ft_putstr_fd(char *str, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putchar_fd(char c, int fd);
void				*ft_calloc(size_t count, size_t size);

/*
** Error management
*/

typedef	enum		e_errors
{
	OK = 1,
	ERR_SYS,
	ERR_ARGNUM,
	ERR_ARGPHL,
	ERR_ARGPHH,
	ERR_ARGTIM,
	ERR_ARGEAT
}					t_errors;

int					errman(int errnum);

#endif
