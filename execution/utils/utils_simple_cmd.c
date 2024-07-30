/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:18:00 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/24 01:15:00 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "pwd"))
		return (0);
	return (1);
}

int	tab_len(char **cmd_tab)
{
	int	i;

	i = 0;
	while (cmd_tab[i])
	{
		i++;
	}
	return (i);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	**add_in_tab(char **cmd_tab, char *str_to_add)
{
	char	**tmp_tab;
	int		i;

	if (!cmd_tab)
		return (NULL);
	i = 0;
	tmp_tab = malloc(sizeof(*tmp_tab) * (tab_len(cmd_tab) + 2));
	if (!tmp_tab)
	{
		free_tab(cmd_tab);
		return (NULL);
	}
	while (cmd_tab[i])
	{
		tmp_tab[i] = ft_strdup(cmd_tab[i]);
		if (!tmp_tab[i])
			return (free_tab(cmd_tab), NULL);
		i++;
	}
	tmp_tab[i] = ft_strdup(str_to_add);
	if (!tmp_tab[i])
		return (free_tab(cmd_tab), NULL);
	tmp_tab[i + 1] = NULL;
	free_tab(cmd_tab);
	return (tmp_tab);
}

char	**last_touch2(char **tab, int i)
{
	int	k;

	k = i + 1;
	while (tab[k])
	{
		tab[k] = tab[k + 1];
		k++;
	}
	return (tab);
}
