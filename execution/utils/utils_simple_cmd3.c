/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simple_cmd3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:15:46 by marechaloli       #+#    #+#             */
/*   Updated: 2024/07/24 01:17:37 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**order_tab(char **tab)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		if (!strcmp("<", tab[i]) || !strncmp(">>", tab[i], 2)
			|| !strncmp(">", tab[i], 1))
		{
			tmp = tab[i];
			tab[i] = tab[i - 1];
			tab[i - 1] = tmp;
		}
		i++;
	}
	return (tab);
}

char	**glue_tab(char **tab, int i)
{
	if (!ft_strcmp("<", tab[i + 1]) || !ft_strcmp(">", tab[i + 1])
		|| !ft_strncmp(tab[i + 1], ">>", 2)
		|| !ft_strncmp(tab[i + 1], "<<", 2))
	{
		tab[i] = ft_strjoin(tab[i], " ");
		tab[i] = ft_strjoin(tab[i], tab[i + 1]);
		tab[i] = ft_strjoin(tab[i], " ");
		tab[i] = ft_strjoin(tab[i], tab[i + 2]);
	}
	else
	{
		tab[i] = ft_strjoin(tab[i], " ");
		tab[i] = ft_strjoin(tab[i], tab[i + 1] + 1);
	}
	return (tab);
}

void	check_tab(char **tab)
{
	int		i;

	i = 0;
	tab = order_tab(tab);
	while (tab[i])
	{
		if (tab[i + 1] && (tab[i + 1][0] == '~' || !ft_strcmp("<", tab[i + 1])
			|| !ft_strcmp(">", tab[i + 1]) || !ft_strncmp(tab[i + 1], ">>", 2)
			|| !ft_strncmp(tab[i + 1], "<<", 2)))
			tab = glue_tab(tab, i);
		if (tab[i + 1] && (!ft_strcmp("<", tab[i + 1])
				|| !ft_strcmp(">", tab[i + 1]) || !ft_strcmp(tab[i + 1], ">>")
				|| !ft_strcmp(tab[i + 1], "<<")))
		{
			tab = last_touch(tab, i);
			i--;
		}
		if ((tab[i + 1] && tab[i + 1][0] == '~'))
		{
			tab = last_touch2(tab, i);
			i--;
		}
		i++;
	}
}

char	**init_simple_cmd(t_tree *tree, char **cmd_tab)
{
	if (!tree || !cmd_tab)
		return (cmd_tab);
	cmd_tab = init_simple_cmd(tree->left, cmd_tab);
	cmd_tab = init_simple_cmd(tree->right, cmd_tab);
	if (tree->type == A_CMD || tree->type == A_PARAM)
		cmd_tab = add_in_tab(cmd_tab, tree->data);
	return (cmd_tab);
}

char	**new_tab(void)
{
	char	**new;

	new = malloc(sizeof(char **));
	if (!new)
		return (NULL);
	*new = NULL;
	return (new);
}
