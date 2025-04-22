/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:12:25 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/22 18:47:03 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define ERROR 1
#define OK 0
#define CONVERT_MICRO 1e3
#define DIE 200

typedef pthread_mutex_t	t_mtx;

typedef struct s_table	t_table;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_philo_status;

typedef struct s_fork
{
	int					fork_id;
	t_mtx				fork;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meals_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_mtx				philo_mutex;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				number_of_meals;
	long				start_simulation;
	bool				end_simulation;
	bool				all_threads_redy;
	long				threads_running_nbr;
	pthread_t			monitor;
	t_mtx				table_mutex;
	t_mtx				write_lock;
	t_fork				*forks;
	t_philo				*philos;
}						t_table;

typedef enum e_opcode
{
	CREATE,
	DETACH,
	JOIN,
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
}						t_opcode;

typedef enum e_timecode
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_time_code;

//---safe---

void					*safe_malloc(size_t bytes);
void					safe_mutex_handle(t_mtx *mutex, t_opcode opcode);

//--util--
long					ft_atol(const char *nptr);
int						is_disit(char **argv);
bool					simulation_finished(t_table *table);
void					wait_all_threads(t_table *table);

//---error
int						error_exit(char *str);
void					mutex_handle_error(int status, t_opcode opcode);
void					safe_thread_handle(pthread_t *thread,
							void *(*foo)(void *), void *data, t_opcode opcode);
//---init---
void					data_init(t_table *table);
void					philo_init(t_table *table);
void					assign_forks(t_philo *philo, t_fork *forks,
							int p_possion);
void					parse_input(t_table *table, char **argv);

//---dinner---
bool					all_theread_running(t_mtx *mutex,
							long threads_running_nbr, long philo_nbr);
void					de_synchronize_philos(t_philo *philo);
void					clean(t_table *table);
void					increase_long(t_mtx *mutex, long *value);
//---get--set---
bool					get_bool(t_mtx *mutex, bool *value);
void					set_bool(t_mtx *mutex, bool *dest, bool value);
long					get_long(t_mtx *mutex, long *value);
void					set_long(t_mtx *mutex, long *dest, long value);
long					get_time(t_time_code time_code);

//---philo
void					eat(t_philo *philo);
void					thinking(t_philo *philo, bool per_simulation);
void					write_status(t_philo_status status, t_philo *philo);
bool					philo_died(t_philo *philo);
void					precise_usleep(long usec, t_table *table);
void					*alone_lol(void *arg);
void					increase_long(t_mtx *mutex, long *value);
void					*dinner_simulation(void *data);
void					*moniter_dinner(void *data);
void					lets_dinner(t_table *table);
void					handle_thread_error(int status, t_opcode opecode);
