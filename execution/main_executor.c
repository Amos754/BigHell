/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:39 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/29 00:44:40 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tree_finder(t_tree *tree, int param, int nb)
{
	if (!tree)
		return (nb);
	if (tree->type == param)
		nb++;
	nb = tree_finder(tree->left, param, nb);
	nb = tree_finder(tree->right, param, nb);
	return (nb);
}

int	ast_executor(t_tree *tree, t_envb *env)
{
	int	return_value;
	int	fd[2];
	int	bad_event;
	int	pipe_counter;
	int	*hd_pipes;

	return_value = 0;
	pipe_counter = tree_finder(tree, A_PIPE, 0);
	if (pipe_counter > 0)
		return (exec_simple_cmd(tree, env));
	if (!do_redirection(tree, 0))
		return (exec_simple_cmd(tree, env));
	return (0);
}
