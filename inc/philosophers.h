/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:12:25 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/21 18:28:39 by hirwatan         ###   ########.fr       */
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

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	int					fork_id;
	t_mtx				fork;
}						t_frok;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meals_time;
	t_frok				*left;
	t_frok				*right;
	pthread_t			thread_id;
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
	t_mtx 				table_mutex;
	t_frok				*forks;
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

//---safe---

void					*safe_malloc(size_t bytes);
void					safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
//---safe---

//--util--
long					ft_atol(const char *nptr);

//---error
int						error_exit(char *str);
void					mutex_handle_error(int status, t_opcode opcode);
static void				handle_thread_error(int status, t_opcode opecode);
void					safe_thread_handle(pthread_t *thread,
							void *(*foo)(void *), void *data, t_opcode opcode);
//---init---
void	data_init(t_table *table);
void	philo_init(t_table *table);
void	assign_forks(t_philo *philo, t_frok *forks, int p_possion);
