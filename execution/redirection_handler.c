/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:47:02 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/17 15:47:36 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hd_handler(char *delimiter, t_tree *ast)
{
	int		hd_pipe[2];
	char	*line;
	int		nbhd;

	line = readline("heredoc> ");
	while (1)
	{
		if (!ft_strcmp(delimiter, line))
			break ;
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
}

int	red_manager(t_tree *ast, int order)
{
	int	fd;

	if (order == 1)
		fd = open(ast->right->right->data, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (order == 2)
		fd = open(ast->right->right->data, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (order == 3)
		fd = open(ast->right->right->data, O_RDONLY);
	else if (order == 4)
		hd_handler((char *)ast->right->right->data, ast);
	if (fd == -1)
		return (-1);
	if (order == 1 || order == 2)
		fd = dup2(fd, STDOUT_FILENO);
	if (order == 3)
		fd = dup2(fd, STDIN_FILENO);
	if (fd == -1)
		return (-1);
	return (0);
}

int	redirection_handler(t_tree *ast)
{
	if (ast->left->type == A_DGREAT)
		return (red_manager(ast, 1));
	if (ast->left->type == A_RED_TO)
		return (red_manager(ast, 2));
	if (ast->left->type == A_RED_FROM)
		return (red_manager(ast, 3));
	if (ast->left->type == A_DLESS)
		return (red_manager(ast, 4));
	return (0);
}

int	do_redirection(t_tree *ast, int error)
{
	if (!ast || (ast && ast->type == A_PIPE))
		return (error);
	error = do_redirection(ast->left, error);
	error = do_redirection(ast->right, error);
	if (error == -1)
		return (error);
	if (ast->reduc == R_IO_FILE || ast->reduc == R_IO_HERE)
	{
		if (ast->left->type == A_DGREAT || ast->left->type == A_RED_FROM
			|| ast->left->type == A_RED_TO || ast->left->type == A_DLESS)
			error = redirection_handler(ast);
	}
	return (error);
}
