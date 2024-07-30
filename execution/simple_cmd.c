/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:49:13 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/26 13:38:33 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**init_pipe_cmd(t_tree *tree, char **cmd_tab)
{
	if (!tree || !cmd_tab)
		return (cmd_tab);
	cmd_tab = init_pipe_cmd(tree->left, cmd_tab);
	cmd_tab = init_pipe_cmd(tree->right, cmd_tab);
	if (tree->type == A_CMD || tree->type == A_PARAM || tree->type == A_FILE)
	{
		if (tree->type == A_PARAM)
			tree->data = ft_strjoin("~", tree->data);
		cmd_tab = add_in_tab(cmd_tab, tree->data);
	}
	if (tree->reduc == R_IO_HERE || tree->reduc == R_IO_FILE)
	{
		cmd_tab = add_in_tab(cmd_tab, tree->left->data);
		if (tree->reduc == R_IO_HERE)
			cmd_tab = add_in_tab(cmd_tab, tree->right->right->data);
	}
	return (cmd_tab);
}

int	executor(char **cmd_tab, t_envb *env)
{
	char	*bin_cmd;
	char	**paths;
	int		return_value;

	paths = get_paths(env->env);
	bin_cmd = get_cmd(paths, cmd_tab[0]);
	if (!bin_cmd)
		return (-1);
	return_value = execve(bin_cmd, cmd_tab, env->env);
	if (return_value == -1)
	{
		if (errno == EAGAIN)
			return_value = 126;
		else
			return_value = 127;
	}
	return (return_value);
}

int	exec_binary(char **cmd_tab, t_envb *env)
{
	pid_t	pid_fork;
	pid_t	pid_wait;
	int		status;
	int		child_value;

	pid_fork = fork();
	if (pid_fork == -1)
		return (-1);
	if (pid_fork == 0)
	{
		// activate_signal();
		child_value = executor(cmd_tab, env);
		free_tab(cmd_tab);
		exit(child_value);
	}
	else
	{
		pid_wait = waitpid(pid_fork, &status, 0);
		if (pid_wait == -1)
			return (-1);
	}
	return (exit_status(status, env));
}

int	exec_builtin(char **cmd_tab, t_envb *env)
{
	int	ac;

	ac = 0;
	while (cmd_tab[ac])
		ac++;
	if (!ft_strcmp("cd", cmd_tab[0]))
		return (env->exstatus = main_cd(ac, cmd_tab, env));
	if (!ft_strcmp("echo", cmd_tab[0]))
		return (env->exstatus = main_echo(ac, cmd_tab, env));
	if (!ft_strcmp("exit", cmd_tab[0]))
		exit(main_exit(ac, cmd_tab));
	if (!ft_strcmp("env", cmd_tab[0]))
		return (env->exstatus = main_env(ac, cmd_tab, env));
	if (!ft_strcmp("export", cmd_tab[0]))
		return (env->exstatus = main_export(ac, cmd_tab, env));
	if (!ft_strcmp("pwd", cmd_tab[0]))
		return (env->exstatus = main_pwd(ac, cmd_tab));
	if (!ft_strcmp("unset", cmd_tab[0]))
		return (env->exstatus = main_unset(ac, cmd_tab, env));
	return (0);
}

int	exec_simple_cmd(t_tree *tree, t_envb *env)
{
	char	**cmd_tab;

	if (tree_finder(tree, A_PIPE, 0) > 0)
	{
		cmd_tab = init_pipe_cmd(tree, new_tab());
		check_tab(cmd_tab);
	}
	else
		cmd_tab = init_simple_cmd(tree, new_tab());
	if (!cmd_tab)
		return (1);
	if (*cmd_tab)
	{
		if (tree_finder(tree, A_PIPE, 0) > 0)
			return (main_pipe(tab_len(cmd_tab), cmd_tab, env));
		if (!is_builtin(cmd_tab[0]))
			return (exec_builtin(cmd_tab, env));
		else
			return (exec_binary(cmd_tab, env));
	}
	else
		free_tab(cmd_tab);
	return (0);
}
