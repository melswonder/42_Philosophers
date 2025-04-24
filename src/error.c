/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:01:53 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/24 09:58:50 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	error_msg(char *str)
{
	printf("%s\n", str);
	return (-1);
}

void	mutex_handle_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if ((EINVAL == status && opcode == LOCK) || opcode == UNLOCK)
		error_msg("Mutex lock failed: maximum recursive locks exceeded.");
	else if (EINVAL == status && INIT == opcode)
		error_msg("The mutex has not been properly initialized");
	else if (EDEADLK == status)
		error_msg("The mutex is already locked by the calling thread");
	else if (EPERM == status)
		error_msg("The calling thread does not own the mutex ");
	else if (ENOMEM == status)
		error_msg("Insufficient memory exists to initialize the mutex");
	else if (EBUSY == status)
		error_msg("The mutex is currently locked.");
}

void	handle_thread_error(int status, t_opcode opecode)
{
	if (status == 0)
		return ;
	if (opecode == EAGAIN)
		error_msg("Insufficient resources to create another thread");
	else if (opecode == EINVAL)
		error_msg("Invalid settings in attr.");
	else if (opecode == EPERM)
		error_msg("No permission parameters specified in attr.");
	else
		error_msg("handle thread error");
}
