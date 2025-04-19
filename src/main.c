/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:41 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/19 18:11:47 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// timestamp_in_ms X has taken a fork
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died
// 人数　死ぬ時間　食べる時間　寝る時間
int	error_exit(char *str)
{
	printf("%s\n", str);
	exit(1);
}

long	ft_atol(const char *nptr)
{
	int		m_flag;
	long	ret;

	m_flag = 1;
	ret = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			m_flag = -1;
	while (*nptr)
	{
		if (*nptr >= '0' && *nptr <= '9')
		{
			ret = ret * 10 + (long)(*nptr - '0');
			nptr++;
		}
		else
			break ;
	}
	ret = ret * m_flag;
	if (ret > INT_MAX || ret < INT_MIN)
		error_exit("LIMIT_ERROR int");
	return (ret);
}

void	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * CONVERT_MICRO;
	table->time_to_eat = ft_atol(argv[3]) * CONVERT_MICRO;
	table->time_to_sleep = ft_atol(argv[4]) * CONVERT_MICRO;
	if (argv[5])
		table->number_of_meals = ft_atol(argv[5]);
	else
		table->number_of_meals = -1;
}

void	data_init(t_table *table)
{
}

void	mutex_handle_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EINVAL)
}

void	mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		pthread_mutex_lock(mutex);
	else if (opcode == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (opcode == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (opcode == DESTROY)
		pthread_mutex_destroy(mutex);
	else
		error_exit("Wrong opcode");
}

int	main(int argc, char *argv[])
{
	t_table *table;
	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		data_init(&table);
		lets_dinner(&table);
	}
	else
		error_exit();
	return (0);
}