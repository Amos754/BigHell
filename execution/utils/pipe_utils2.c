/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmarech <olmarech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:57:57 by marechaloli       #+#    #+#             */
/*   Updated: 2024/07/30 15:03:08 by olmarech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	red_deal_in(char *cmd, t_command *cmd_node, t_piped *piped, int fd)
{
	fd = open(cmd_node->input_file, O_RDONLY);
	if (fd == ERROR)
	{
		perror("Input file open error");
		exit(1);
	}
	dup2(fd, 0);
	execve(cmd, cmd_node->args, piped->env);
	close(fd);
}

void	red_deal_out(char *cmd, t_command *cmd_node, t_piped *piped, int fd)
{
	if (cmd_node->append_output)
		fd = open(cmd_node->output_file, O_WRONLY | O_CREAT
				| O_APPEND, 0644);
	else
		fd = open(cmd_node->output_file, O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
	if (fd == ERROR)
	{
		perror("Output file open error");
		exit(1);
	}
	dup2(fd, 1);
	execve(cmd, cmd_node->args, piped->env);
	close(fd);
}

void	close_pipe(t_piped *piped)
{
	int	i;

	i = -1;
	while (++i < piped->num_cmds - 1)
	{
		close(piped->fd[i][0]);
		close(piped->fd[i][1]);
	}
}

int	utils(int fd, t_piped *piped, int option, int cmd_index)
{
	if (option == 1)
	{
		if (cmd_index == 0)
			dup2(piped->fd[cmd_index][1], 1);
		else if (cmd_index == piped->num_cmds - 1)
			dup2(piped->fd[cmd_index - 1][0], 0);
		else
		{
			dup2(piped->fd[cmd_index - 1][0], 0);
			dup2(piped->fd[cmd_index][1], 1);
		}
	}
	else if (option == 2 || option == 3)
	{
		if (fd < 0)
		{
			if (option == 2)
				perror("Input file open error");
			else
				perror("Output file open error");
			return (1);
		}
		return (0);
	}
	return (0);
}

void	adj_exec(t_command *cmd_node, t_piped *piped, char *cmd, int cmd_index)
{
	int	fd;

	if (cmd_node->input_file)
	{
		fd = open(cmd_node->input_file, O_RDONLY);
		if (utils(fd, NULL, 2, 0))
			exit(1);
		dup2(fd, 0);
	}
	if (cmd_node->output_file)
	{
		if (cmd_node->append_output)
			fd = open(cmd_node->output_file, O_WRONLY
					| O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd_node->output_file, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		if (utils(fd, NULL, 3, 0))
			exit(1);
		dup2(fd, 1);
	}
	if (cmd_node->input_file || cmd_node->output_file)
	{
		close(fd);
		execve(cmd, cmd_node->args, piped->env);
	}
	utils(0, piped, 1, cmd_index);
}
