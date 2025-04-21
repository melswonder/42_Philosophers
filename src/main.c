/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:41 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/21 18:30:49 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// timestamp_in_ms X has taken a fork
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died
// 人数　死ぬ時間　食べる時間　寝る時間

void	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]); //正の数
	table->time_to_die = ft_atol(argv[2]) * CONVERT_MICRO;
	table->time_to_eat = ft_atol(argv[3]) * CONVERT_MICRO;
	table->time_to_sleep = ft_atol(argv[4]) * CONVERT_MICRO;
	if (argv[5])
		table->number_of_meals = ft_atol(argv[5]); //有効かどうか
	else
		table->number_of_meals = -1;
}

void	data_init(t_table *table)
{
	int	i;

	table->end_simulation = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	safe_mutex_handle(&table->table_mutex,INIT);
	table->forks = safe_malloc(sizeof(t_frok) * table->number_of_meals);
	i = 0;
	while (i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
	}
	philo_init(table);
}
void	dinner(void)
{
}

void	lets_dinner(t_table *table)
{
	int	i;

	i = 0;
	if (table->number_of_meals == 0)
		return ;
	else if (table->number_of_meals == 1)
		;
	else
	{
		while (i < table->philo_nbr)
		{
			safe_thread_handle(table->philos[i].thread_id, dinner,
				&table->philos[i], CREATE);
			i++;
		}
	}
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		data_init(&table);
		lets_dinner(&table);
	}
	else
		error_exit("Error missing argment");
	return (0);
}

// 1:05:04