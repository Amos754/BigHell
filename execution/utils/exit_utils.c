/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:07:12 by marechaloli       #+#    #+#             */
/*   Updated: 2024/07/25 01:22:57 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_status(int status, t_envb *env)
{
	if (WIFSIGNALED(status))
	{
		env->exstatus = 128 + WTERMSIG(status);
		return (128 + WTERMSIG(status));
	}
	env->exstatus = WEXITSTATUS(status);
	return (WEXITSTATUS(status));
}
