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

int	go_home2(char **envp, t_envb *env)
{
	int		i;
	char	buff[1024];

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "HOME=", 5))
		{
			if (chdir(envp[i] + 5) == -1)
			{
				write(2, "minishell: cd: ", 16);
				perror(envp[i] + 5);
				return (3);
			}
			return (0);
		}
		i++;
	}
	return (2);
}

int	trash(t_envb *env)
{
	write(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 108);
	change_old_pwd(env, env->pwd);
	change_pwd(env, 1);
	go_home2(env->env, env);
	return (0);
}
