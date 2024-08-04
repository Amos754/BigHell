/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:09:46 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/31 02:32:08 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_bison(void)
{
	char	*pwd;
	char	*buf;
	long	size;

	size = pathconf(".", _PC_PATH_MAX);
	buf = malloc((size_t)size);
	if (!buf)
		return (".");
	pwd = getcwd(buf, size);
	if (pwd == NULL)
		return (".");
	return (pwd);
}

void	free_env(t_envb *env)
{
	free(env->pwd);
	free(env);
}

int	main(int ac, char **av, char **envp)
{
	t_token		*input;
	char		*inp;
	t_tree		*tree;
	t_table		**parsingtable;
	t_envb		*env;
	char **test;
	char *good;
	int	i;
	int	fd[2];
	char	*pt_path;

	if (!(envp[0]))
		exit (1);
	else
		env = env_init(envp);
	pt_path = ft_strjoin(new_bison(), BISON_AUTOMATON);
	while (1)
	{
		signal_handlers();
		inp = readline("\033[1;35mSUPRAHELL \e[0m");
		if (!inp)
		{
			rl_on_new_line();
			rl_redisplay();
			printf("exit\n");
			free_env(env);
			exit(0);
		}
		fd[0] = dup(0);
		fd[1] = dup(1);
		add_history((char *)inp);
		input = ft_lexer(inp);
		parsingtable = ft_init_parsing_table(pt_path);
		tree = syntax_analysis(input, parsingtable);
		if (tree)
			ast_executor(tree, env);
		fd[0] = dup2(fd[0], 0);
		fd[1] = dup2(fd[1], 1);
	}
	free_env(env);
	reset_signal_handlers();
}
