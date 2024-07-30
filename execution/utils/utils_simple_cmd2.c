/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simple_cmd2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:19:36 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/24 01:14:34 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**go_to_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*good_cmd;

	while (*paths)
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		good_cmd = ft_strjoin(*paths, cmd);
		if (access(good_cmd, F_OK | X_OK) == 0)
			return (good_cmd);
		free(good_cmd);
		paths++;
	}
	return (NULL);
}

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;
	char	*tmp;

	paths = go_to_path(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		if (!paths[i])
		{
			free_tab(paths);
			return (NULL);
		}
		free(tmp);
		i++;
	}
	return (paths);
}

int	env_size(char **env)
{
	int	size;

	size = 0;
	while (env[size] != NULL)
		size++;
	return (size);
}

char	**last_touch(char **tab, int i)
{
	int	k;

	k = i + 1;
	while (tab[k])
	{
		tab[k] = tab[k + 1];
		k++;
	}
	k = i + 1;
	while (tab[k])
	{
		tab[k] = tab[k + 1];
		k++;
	}
	return (tab);
}
