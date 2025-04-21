/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:00:33 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/21 17:53:06 by hirwatan         ###   ########.fr       */
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
			error_exit("parce error");
	}
	ret = ret * m_flag;
	if (ret > INT_MAX || ret < INT_MIN)
		error_exit("LIMIT_ERROR int");
	return (ret);
}
