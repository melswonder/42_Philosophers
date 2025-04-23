/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:41 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/23 09:29:53 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc == 5 || argc == 6)
	{
		table = safe_malloc(sizeof(t_table));
		memset(table, 0, sizeof(t_table));
		parse_input(table, argv);
		data_init(table);
		lets_dinner(table);
		clean(table);
	}
	else
		error_exit("Error missing argment");
	return (0);
}
