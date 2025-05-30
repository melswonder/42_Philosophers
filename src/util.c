/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:00:33 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/24 09:55:23 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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
			return (error_msg("parce error"));
	}
	ret = ret * m_flag;
	if (ret > INT_MAX || ret < INT_MIN)
		return (error_msg("LIMIT_ERROR int"));
	return (ret);
}

int	is_disit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	char_c;

	ptr = (unsigned char *)s;
	char_c = (unsigned char)c;
	while (n--)
	{
		*ptr = char_c;
		ptr++;
	}
	return ((void *)s);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}

// spinlock
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_redy))
		;
}
