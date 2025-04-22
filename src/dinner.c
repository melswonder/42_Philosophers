/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:03:31 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/22 17:59:58 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*alone_lol(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meals_time,
		get_time(MILLISECOND));
	// increase_long(TAKE_FIRST_FORK, philo);
	safe_mutex_handle(&philo->left->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(DIE);
	return (NULL);
}

void	increase_long(t_mtx *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meals_time,
		get_time(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	de_synchronize_philos(philo);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, true);
	}
	return (NULL);
}

void	*moniter_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_theread_running(&table->table_mutex, table->threads_running_nbr,
			table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			if (philo_died(&table->philos[i]))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i);
			}
			i++;
		}
	}
	return (NULL);
}

void	lets_dinner(t_table *table)
{
	int	i;

	i = 0;
	if (table->number_of_meals == 0)
		return ;
	else if (table->number_of_meals == 1)
		safe_thread_handle(&table->philos[0].thread_id, alone_lol,
			&table->philos[0], CREATE);
	else
	{
		while (i++ < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	safe_thread_handle(&table->monitor, moniter_dinner, table, CREATE);
	table->start_simulation = get_time(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_redy, true);
	i = 0;
	while (i++ < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
