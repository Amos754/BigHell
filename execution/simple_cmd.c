/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:49:13 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/04 02:10:50 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**init_pipe_cmd(t_tree *tree, char **cmd_tab, t_envb *env)
{
	if (!tree || !cmd_tab)
		return (cmd_tab);
	cmd_tab = init_pipe_cmd(tree->left, cmd_tab, env);
	cmd_tab = init_pipe_cmd(tree->right, cmd_tab, env);
	if (tree->type == A_CMD || tree->type == A_PARAM || tree->type == A_FILE)
	{
		if (tree->type == A_PARAM)
			tree->data = ft_strjoin("~", tree->data);
		cmd_tab = add_in_tab(cmd_tab, tree->data, env);
	}
	if (tree->reduc == R_IO_HERE || tree->reduc == R_IO_FILE)
	{
		cmd_tab = add_in_tab(cmd_tab, tree->left->data, env);
		if (tree->reduc == R_IO_HERE)
			cmd_tab = add_in_tab(cmd_tab, tree->right->right->data, env);
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

int	executor(char **cmd_tab, t_envb *env)
{
	char	*bin_cmd;
	char	**paths;
	int		return_value;

	paths = get_paths(env->env);
	bin_cmd = get_cmd(paths, cmd_tab[0]);
	return_value = execve(bin_cmd, cmd_tab, env->env);
	error_handle(cmd_tab, return_value);
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
		signal_handlers();
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
		exit(main_exit(ac, cmd_tab, env));
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

char	*check_path_dollar(char *str, t_envb *env)
{
	char	**tmp_tab;
	int		i;
	char	*final;
	char	*bis;
	int		info;

	i = 0;
	info = 0;
	if (str[0] == '/' || str[ft_strlen(str) - 1] == '/')
	{
		if (str[0] == '/' && str[ft_strlen(str) - 1] != '/')
			info = 1;
		else if (str[0] != '/' && str[ft_strlen(str) - 1] == '/')
			info = 2;
		else if (str[0] == '/' && str[ft_strlen(str) - 1] == '/')
			info = 3;
	}
	tmp_tab = ft_split(str, '/');
	while (tmp_tab[i])
	{
		if (tmp_tab[i][0] == '$')
			tmp_tab[i] = dollar_parse(tmp_tab[i] + 1, env);
		i++;
	}
	i = 1;
	if (info == 1 || info == 3)
	{
		final = ft_strjoin("/", tmp_tab[0]);
		final = ft_strjoin(final, "/");
	}
	else
		final = ft_strjoin(tmp_tab[0], "/");
	while (tmp_tab[i])
	{
		if (tmp_tab[i + 1] || (!tmp_tab[i + 1] && (info == 2 || info == 3)))
			bis = ft_strjoin(tmp_tab[i], "/");
		else
			bis = tmp_tab[i];
		final = ft_strjoin(final, bis);
		i++;
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

int	exec_simple_cmd(t_tree *tree, t_envb *env)
{
	char	**cmd_tab;

	if (tree_finder(tree, A_PIPE, 0) > 0)
	{
		cmd_tab = init_pipe_cmd(tree, new_tab(), env);
		cmd_tab = check_dollar(cmd_tab, env);
		check_tab(cmd_tab);
	}
	else
		cmd_tab = init_simple_cmd(tree, new_tab(), env);
	cmd_tab = check_dollar(cmd_tab, env);
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
