/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:01:53 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/21 17:02:54 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	error_exit(char *str)
{
	printf("%s\n", str);
	exit(1);
}

static void	mutex_handle_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EINVAL == status && opcode == LOCK || opcode == UNLOCK)
		error_exit("Mutex lock failed: maximum recursive locks exceeded.");
	else if (EINVAL == status && INIT == opcode)
		error_exit("The mutex has not been properly initialized");
	else if (EDEADLK == status)
		error_exit("The mutex is already locked by the calling thread");
	else if (EPERM == status)
		error_exit("The calling thread does not own the mutex ");
	else if (ENOMEM == status)
		error_exit("Insufficient memory exists to initialize the mutex");
	else if (EBUSY == status)
		error_exit("The mutex is currently locked.");
}

static void	handle_thread_error(int status, t_opcode opecode)
{
	// error	がない時はそのまま終わる
	if (status == 0)
		return ;
	if (opecode == EAGAIN)
		error_exit("Insufficient resources to create another thread");
	else if (opecode == EINVAL)
		error_exit("Invalid settings in attr.");
	else if (opecode == EPERM)
		error_exit("No permission parameters specified in attr.");
	else
		error_exit("handle thread error");
}
