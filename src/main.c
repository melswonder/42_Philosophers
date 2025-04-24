/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:41 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/24 09:57:39 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc == 5 || argc == 6)
	{
		table = safe_malloc(sizeof(t_table));
		ft_memset(table, 0, sizeof(t_table));
		if (parse_input(table, argv))
			return (1);
		data_init(table);
		lets_dinner(table);
		clean(table);
	}
	else
		error_msg("Error missing argment");
	return (0);
}
