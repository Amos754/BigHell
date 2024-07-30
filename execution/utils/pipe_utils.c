/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:53:23 by marechaloli       #+#    #+#             */
/*   Updated: 2024/07/28 23:11:46 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	*create_command_node(char *cmd)
{
	t_command	*new_node;

	new_node = malloc(sizeof(t_command));
	if (!new_node)
		return (NULL);
	new_node->args = ft_split(cmd, ' ');
	new_node->output_file = NULL;
	new_node->input_file = NULL;
	new_node->append_output = 0;
	new_node->next = NULL;
	return (new_node);
}

void	add_command(t_piped *piped, char *cmd)
{
	t_command	*new_node;
	t_command	*current;

	new_node = create_command_node(cmd);
	if (!new_node)
		return ;
	if (!piped->commands)
		piped->commands = new_node;
	else
	{
		current = piped->commands;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

void	parse_redirections(t_command *cmd_node)
{
	int	i;

	i = 0;
	while (cmd_node->args[i])
	{
		if (strcmp(cmd_node->args[i], ">") == 0)
		{
			cmd_node->output_file = strdup(cmd_node->args[i + 1]);
			cmd_node->args[i] = NULL;
		}
		else if (strcmp(cmd_node->args[i], ">>") == 0)
		{
			cmd_node->output_file = strdup(cmd_node->args[i + 1]);
			cmd_node->append_output = 1;
			cmd_node->args[i] = NULL;
		}
		else if (strcmp(cmd_node->args[i], "<") == 0)
		{
			cmd_node->input_file = strdup(cmd_node->args[i + 1]);
			cmd_node->args[i] = NULL;
		}
		i++;
	}
}

void	init_creat(t_piped *piped, char **envp, int num_cmds, char **av)
{
	int	i;

	i = 0;
	piped->num_cmds = num_cmds;
	piped->env = envp;
	piped->commands = NULL;
	while (i < num_cmds)
		add_command(piped, av[i++]);
	piped->fd = malloc(sizeof(int *) * (num_cmds - 1));
}

int	creat_pipe(t_piped *piped, char **envp, char **av, int num_cmds)
{
	int			i;
	t_command	*current;

	init_creat(piped, envp, num_cmds, av);
	i = -1;
	while (++i < num_cmds - 1)
	{
		piped->fd[i] = malloc(sizeof(int) * 2);
		if (pipe(piped->fd[i]) == ERROR)
			return (0);
	}
	piped->pid = malloc(sizeof(pid_t) * num_cmds);
	piped->stdin_cpy = dup(0);
	piped->stdout_cpy = dup(1);
	i = 0;
	while (strncmp("PATH=", envp[i], 5))
		i++;
	piped->paths = ft_split(envp[i] + 5, ':');
	current = piped->commands;
	while (current)
	{
		parse_redirections(current);
		current = current->next;
	}
	return (1);
}
