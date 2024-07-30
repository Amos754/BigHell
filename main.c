/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:09:46 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/30 01:49:18 by marechaloli      ###   ########.fr       */
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
		env = env_init(NULL);
	else
		env = env_init(envp);
	// printf("%s\n", env->env[i]);
	pt_path = ft_strjoin(new_bison(), BISON_AUTOMATON);
	while (1)
	{
		inp = readline("\033[1;35mSUPRAHELL \e[0m");
		fd[0] = dup(0);
		fd[1] = dup(1);
		add_history((char *)inp);
		input = ft_lexer(inp);
		parsingtable = ft_init_parsing_table(pt_path);
		tree = syntax_analysis(input, parsingtable);
		if (!tree)
			printf("Tree is NULL\n");
		else
			ast_executor(tree, env);
		fd[0] = dup2(fd[0], 0);
		fd[1] = dup2(fd[1], 1);
	}
}
