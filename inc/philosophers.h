/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:12:25 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/19 18:09:47 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

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
	long				number_of_meals;
	bool				full;
	long				last_meals_time;
	t_frok				*left;
	t_frok				*right;
	pthread_t			thread_id;
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
