/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simple_cmd4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:15:46 by marechaloli       #+#    #+#             */
/*   Updated: 2024/08/04 23:39:56 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	info_path(char *str)
{
	int	info;

	info = 0;
	if (str[0] == '/' && str[ft_strlen(str) - 1] != '/')
		info = 1;
	else if (str[0] != '/' && str[ft_strlen(str) - 1] == '/')
		info = 2;
	else if (str[0] == '/' && str[ft_strlen(str) - 1] == '/')
		info = 3;
	return (info);
}

char	*check_path_dollar(char *str, t_envb *env)
{
	char	**tmp_tab;
	int		i;
	char	*final;
	char	*bis;
	int		info;

	i = -1;
	info = info_path(str);
	tmp_tab = ft_split(str, '/');
	while (tmp_tab[++i])
		if (tmp_tab[i][0] == '$')
			tmp_tab[i] = dollar_parse(tmp_tab[i] + 1, env);
	i = 0;
	if (info == 1 || info == 3)
		final = ft_strjoin(ft_strjoin("/", tmp_tab[0]), "/");
	else
		final = ft_strjoin(tmp_tab[0], "/");
	while (tmp_tab[++i])
	{
		bis = tmp_tab[i];
		if (tmp_tab[i + 1] || (!tmp_tab[i + 1] && (info == 2 || info == 3)))
			bis = ft_strjoin(tmp_tab[i], "/");
		final = ft_strjoin(final, bis);
	}
	return (final);
}

char	**check_dollar(char **cmd_tab, t_envb *env)
{
	int	i;

	i = 0;
	while (cmd_tab[i])
	{
		if (cmd_tab[i][0] == '$' && !strchr(cmd_tab[i], '/'))
			cmd_tab[i] = dollar_parse(cmd_tab[i] + 1, env);
		else if (strchr(cmd_tab[i], '/'))
			cmd_tab[i] = check_path_dollar(cmd_tab[i], env);
		i++;
	}
	return (cmd_tab);
}

void	error_handle(char **cmd_tab, int option)
{
	if (option == 1)
	{
		write(2, "minishell: ", ft_strlen("minishell: "));
		perror(cmd_tab[0]);
	}
	else
	{
		write(2, "minishell: ", ft_strlen("minishell: "));
		write(2, cmd_tab[0], ft_strlen(cmd_tab[0]));
		write(2, ": command not found\n", ft_strlen(": command not found\n"));
	}
}

int	open_files(t_command *cmd_node)
{
	int	fd;

	if (cmd_node->input_file)
		fd = open(cmd_node->input_file, O_RDONLY);
	else if (cmd_node->append_output)
		fd = open(cmd_node->output_file, W | C | A, 0644);
	else
		fd = open(cmd_node->output_file, W | C | T, 0644);
	return (fd);
}
