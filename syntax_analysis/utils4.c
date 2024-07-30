/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:06:28 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/19 15:06:32 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** TREE TYPE FIXING
*/

static void	ms_visit_fix_types(t_tree *node)
{
	if (!node)
		return ;
	if (node->reduc == R_FILENAME)
		node->right->type = A_FILE;
	if (node->reduc == R_HERE_END)
		node->right->type = A_LIMITER;
	if (node->reduc > R_CMD_WORD)
	{
		if (node->left && node->left->type == A_CMD)
			node->left->type = A_PARAM;
		if (node->right && node->right->type == A_CMD)
			node->right->type = A_PARAM;
	}
	ms_visit_fix_types(node->left);
	ms_visit_fix_types(node->right);
}

t_tree	*ms_fix_param_types(t_tree *tree)
{
	if (tree && tree->type == -1)
		tree->type = -2;
	ms_visit_fix_types(tree);
	return (tree);
}

/*
** REMOVE NODE FROM LIST
** Remove a node from the list that will be attached under a reduction
** node
*/

void	ms_remove_node_from_list(t_tree **tree, t_tree *node)
{
	t_tree	*previous;
	t_tree	*tmp;

	previous = NULL;
	tmp = NULL;
	if (*tree == node)
	{
		*tree = node->next;
		return ;
	}
	else
	{
		previous = NULL;
		tmp = *tree;
		while (tmp)
		{
			if (tmp == node)
			{
				previous->next = tmp->next;
				return ;
			}
			previous = tmp;
			tmp = tmp->next;
		}
	}
}
