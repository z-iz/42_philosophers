/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 23:38:20 by larosale          #+#    #+#             */
/*   Updated: 2020/12/09 13:16:00 by larosale         ###   ########.fr       */
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

# define MAX_THREADS	(200)
# define MIN_TIME		(60)
# define CHECK_PERIOD	(1000)

# define LEFTY			(0)
# define RIGHTY			(1)

# define LOCK			(0)
# define UNLOCK			(1)

extern				pthread_mutex_t *g_forks;
extern				pthread_mutex_t g_write_lock;

typedef enum		e_states
{
	THINKING = 1,
	TAKEN_LFORK,
	TAKEN_RFORK,
	TAKEN_FORKS,
	EATING,
	SLEEPING,
	ATE,
	DIED
}					t_states;

typedef struct		s_params
{
	int				thr_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eats;
	long			start_time;
}					t_params;

typedef struct		s_philos
{
	int				num;
	int				type;
	pthread_t		thread;
	t_states		state;
	int				num_ate;
	int				last_eat;
	pthread_mutex_t	state_lock;
	t_params		*params;
}					t_philos;

/*
** Philosophers - initialization
*/

t_philos			*create_philos(t_params *params);
int					create_forks(t_params *params);

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
