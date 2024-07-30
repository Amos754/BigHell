/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:08:30 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/19 15:08:32 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*res;
	char	*temp;

	res = NULL;
	res = malloc(count * size);
	if (!res)
		return (NULL);
	temp = res;
	i = 0;
	while (i < count * size)
		temp[i++] = 0;
	return (res);
}

/*
** CLEAR INPUT
** At the end of the parser or if an error occurs during the parsing.
*/

void	ms_clear_input(t_token *input)
{
	t_token	*next;

	next = NULL;
	while (input)
	{
		next = input->next;
		free(input->value);
		free(input);
		input = next;
	}
}

/*
** CLEAR TREE
** At the end of the parser or if an error occurs during the parsing.
*/

void	ms_clear_tree(t_tree **node)
{
	if (*node)
	{
		ms_clear_tree(&(*node)->left);
		ms_clear_tree(&(*node)->right);
		if (!(*node)->left && !(*node)->right)
		{
			free((*node)->data);
			free(*node);
			*node = NULL;
		}
	}
}

/*
** PARSER CLEANING
*/

void	ms_parser_cleaning(\
	t_tree **tree, t_stack *stack, t_token *input, int ret)
{
	if (ret == -1)
		ms_clear_tree(tree);
	ms_clear_stack(stack);
	ms_clear_input(input);
}
