/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:01:38 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/22 18:47:19 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	assign_forks(t_philo *philo, t_fork *forks, int p_possion)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(p_possion + 1) % philo_nbr];
	philo->second_fork = &forks[p_possion];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[p_possion];
		philo->second_fork = &forks[(p_possion + 1) % philo_nbr];
	}
}

void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
		i++;
	}
}

void	data_init(t_table *table)
{
	int	i;

	table->end_simulation = false;
	table->all_threads_redy = false;
	table->threads_running_nbr = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	safe_mutex_handle(&table->table_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	safe_mutex_handle(&table->write_lock, INIT);	
	i = 0;
	while (i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
	}
	set_bool(&table->table_mutex, &table->all_threads_redy, true);
	philo_init(table);
}

void	parse_input(t_table *table, char **argv)
{
	// if (is_disit(argv))
	// 	error_exit("error invalid input");
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * CONVERT_MICRO;
	table->time_to_eat = ft_atol(argv[3]) * CONVERT_MICRO;
	table->time_to_sleep = ft_atol(argv[4]) * CONVERT_MICRO;
	if (argv[5])
		table->number_of_meals = ft_atol(argv[5]);
	else
		table->number_of_meals = -1;
}
