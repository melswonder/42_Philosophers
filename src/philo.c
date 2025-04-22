/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:39:08 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/22 13:44:55 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->left->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	safe_mutex_handle(&philo->right->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meals_time,
		get_time(MICROSECOND));
	philo->meals_counter++;
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->number_of_meals > 0
		&& philo->meals_counter == philo->table->number_of_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->left->fork, UNLOCK);
	safe_mutex_handle(&philo->right->fork, UNLOCK);
}

void	thinking(t_philo *philo, bool per_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!per_simulation)
		write_status(THINKING, philo);
	write_status(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_die;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > CONVERT_MICRO)
			usleep(rem / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meals_time);
	t_to_die = philo->table->time_to_die;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	if (philo->full)
		return ;
	elapsed = get_time(MICROSECOND);
	safe_mutex_handle(&philo->table->write_lock, LOCK);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_finished(philo->table))
		printf("%ld %d has taken a fork\n", elapsed, philo->id);
	else if ((status == EATING) && !simulation_finished(philo->table))
		printf("%ld %d is eating\n", elapsed, philo->id);
	else if ((status == SLEEPING) && !simulation_finished(philo->table))
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	else if ((status == THINKING) && !simulation_finished(philo->table))
		printf("%ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%ld %d died\n", elapsed, philo->id);
	safe_mutex_handle(&philo->table->write_lock, UNLOCK);
}
