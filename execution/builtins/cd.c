/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:11:38 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/29 00:51:21 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	change_pwd(t_envb *env)
{
	int		i;
	char	*buff;

	i = 0;
	while (ft_strncmp(env->env[i], "PWD=", 4))
		i++;
	buff = malloc(1024);
	getcwd(buff, 1024);
	buff = ft_strjoin("PWD=", buff);
	if (env->env[i])
		env->env[i] = buff;
	return (1);
}

int	go_to_directory(char *buff, char *dir, t_envb *env)
{
	char	**totalpath;
	char	*buff2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	totalpath = ft_split(buff, '/');
	while (totalpath[i])
		i++;
	j = i + 1;
	i = 0;
	while (i < j)
	{
		if (totalpath[i])
			buff2 = ft_strjoin(buff2, totalpath[i]);
		else
			buff2 = ft_strjoin(buff2, dir);
		buff2 = ft_strjoin(buff2, "/");
		i++;
	}
	change_pwd(env);
	return (chdir(buff2));
}

int	go_home(char **envp, t_envb *env)
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
				change_pwd(env);
				return (3);
			}
			change_pwd(env);
			return (0);
		}
		i++;
	}
	change_pwd(env);
	return (2);
}

void	change_old_pwd(t_envb *env, char *buff)
{
	int	i;

	i = 0;
	while (ft_strncmp(env->env[i], "OLDPWD=", 7))
		i++;
	buff = ft_strjoin("OLDPWD=", buff);
	env->oldpwd = buff;
	if (env->env[i])
		env->env[i] = buff;
}

int	main_cd(int ac, char **av, t_envb *env)
{
	char	*buff2;
	int		return_value;

	buff2 = get_pwd(buff2);
	if (ac == 1)
	{
		change_old_pwd(env, buff2);
		return (free(buff2), cd_error(NULL, go_home(env->env, env)));
	}
	else if (ac == 2 && !ft_strncmp(av[1], "-", ft_strlen(av[1])))
	{
		if (chdir(env->oldpwd + 7) == -1 && change_pwd(env))
			return (cd_error(av, 4));
		printf("%s\n", env->oldpwd + 7);
		change_old_pwd(env, buff2);
		free(buff2);
	}
	else
	{
		change_old_pwd(env, buff2);
		free(buff2);
		if (chdir(av[1]) == -1 && change_pwd(env))
			return (cd_error(av, 1));
	}
	return (change_pwd(env), 0);
}
