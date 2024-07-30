/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmarech <olmarech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:29:42 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/30 14:59:15 by olmarech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd_pipe(t_piped *piped, char *av)
{
	int		i;
	char	*fullcmd;
	char	*tmp;

	i = 0;
	if (!is_builtin(av))
		return (av);
	while (piped->paths[i])
	{
		tmp = ft_strjoin(piped->paths[i], "/");
		fullcmd = ft_strjoin(tmp, av);
		free(tmp);
		if (access(fullcmd, F_OK | X_OK) == 0)
			return (fullcmd);
		free(fullcmd);
		i++;
	}
	return (NULL);
}

void	red_dealer(char *cmd, t_command *cmd_node, t_piped *piped)
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmd_node->input_file)
			red_deal_in(cmd, cmd_node, piped, fd);
		if (cmd_node->output_file)
			red_deal_out(cmd, cmd_node, piped, fd);
	}
	else
	{
		wait(&pid);
		close(fd);
	}
}

void	execute_command(t_piped *piped, int cmd_index, t_envb *env)
{
	t_command	*cmd_node;
	pid_t		pid;
	char		*cmd;
	int			i;

	i = -1;
	cmd_node = piped->commands;
	while (++i < cmd_index)
		cmd_node = cmd_node->next;
	cmd = get_cmd_pipe(piped, cmd_node->args[0]);
	if (!cmd)
	{
		perror("Command not found");
		exit(1);
	}
	adj_exec(cmd_node, piped, cmd, cmd_index);
	close_pipe(piped);
	if (!is_builtin(cmd_node->args[0]))
	{
		exec_builtin(cmd_node->args, env);
		exit(0);
	}
	execve(cmd, cmd_node->args, piped->env);
	perror("execve failed");
	exit(1);
}

int	end_process(t_piped *piped, t_envb *env)
{
	int	status;
	int	i;

	i = 0;
	while (i < piped->num_cmds - 1)
	{
		close(piped->fd[i][0]);
		close(piped->fd[i][1]);
		i++;
	}
	i = 0;
	while (i < piped->num_cmds)
	{
		waitpid(piped->pid[i], &status, 0);
		i++;
	}
	dup2(piped->stdout_cpy, 0);
	dup2(piped->stdin_cpy, 1);
	close(piped->stdin_cpy);
	close(piped->stdout_cpy);
	return (exit_status(status, env));
}

int	main_pipe(int ac, char **av, t_envb *env)
{
	t_piped	piped;
	int		i;

	i = 0;
	if (!creat_pipe(&piped, env->env, av, ac))
	{
		printf("Pipe error\n");
		return (1);
	}
	while (i < ac)
	{
		piped.pid[i] = fork();
		if (piped.pid[i] == 0)
			execute_command(&piped, i, env);
		i++;
	}
	return (end_process(&piped, env));
}
