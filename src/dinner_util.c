/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:35:09 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/22 18:05:21 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	all_theread_running(t_mtx *mutex, long threads, long philo_nbr)
{
	bool	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = (threads == philo_nbr);
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	de_synchronize_philos(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, false);
	}
}

void	clean(t_table *table)
{
    int i;

    i = 0;
    while (i < table->philo_nbr)
    {
        safe_mutex_handle(&table->philos[i].philo_mutex, DESTROY);
        safe_mutex_handle(&table->forks[i].fork, DESTROY);
        i++;
    }
    safe_mutex_handle(&table->table_mutex, DESTROY);
    safe_mutex_handle(&table->write_lock, DESTROY);
    free(table->philos);
    free(table->forks);
    free(table);
}
