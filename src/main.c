/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:41 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/22 18:29:50 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		data_init(&table);
		lets_dinner(&table);
		clean(&table);
	}
	else
		error_exit("Error missing argment");
	return (0);
}
