/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:05:26 by marechaloli       #+#    #+#             */
/*   Updated: 2024/07/29 00:54:48 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cd_error(char **av, int nbr)
{
	if (nbr == 1)
	{
		write(2, "minishell: cd: ", 16);
		perror(av[1]);
		return (1);
	}
	else if (nbr == 2)
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		return (1);
	}
	else if (nbr == 3)
		return (1);
	else if (nbr == 4)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 31);
		return (1);
	}
	return (0);
}

char	*get_pwd(char *buff)
{
	buff = malloc(1024);
	buff = getcwd(buff, 1024);
	return (buff);
}
