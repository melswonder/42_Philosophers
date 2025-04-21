/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:01:38 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/21 17:02:56 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	assign_forks(t_philo *philo, t_frok *forks, int p_possion)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->right = &forks[(p_possion + 1) % philo_nbr];
	philo->left = &forks[p_possion];
	if (philo->id % 2)
	{
		philo->right = &forks[p_possion];
		philo->left = &forks[(p_possion + 1) % philo_nbr];
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
		assign_forks(philo, table->forks, i);
		i++;
	}
}
