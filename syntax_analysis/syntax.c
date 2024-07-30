/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:02:19 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/25 01:03:01 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	shift_to_stack(t_table *table_entry,
		t_stack **stack, t_token **token)
{
	t_stack	*new_stack;

	new_stack = (t_stack *)malloc(sizeof(*new_stack));
	if (!new_stack)
		return (-1);
	new_stack->state = -1;
	new_stack->type = (*token)->type;
	new_stack->data = (*token)->value;
	(*token)->value = NULL;
	new_stack->quote = (*token)->quote;
	new_stack->next = *stack;
	*stack = new_stack;
	if (table_entry->state == -1)
		return (-1);
	if (change_stack_state(table_entry->next_state, stack) == -1)
		return (-1);
	(*token) = (*token)->next;
	return (0);
}

/*
Takes the entry with state 0 (common convention) and type as token type!
if not token type by default type -1: default choice -1!
If input type is not equal to any pt token type!
*/

t_table	*getentry(t_token *token, t_table **parsingtable, t_stack *stack)
{
	int		i;
	int		t_type;
	t_table	*table_entry;

	if (!stack)
		return (NULL);
	i = -1;
	t_type = -1;
	table_entry = NULL;
	if (token != NULL)
		t_type = token->type;
	while (parsingtable[++i])
	{
		if (parsingtable[i]->state == stack->state)
		{
			if (parsingtable[i]->token_type == t_type)
				return (parsingtable[i]);
			else if (parsingtable[i]->token_type == -1)
				table_entry = parsingtable[i];
		}
	}
	return (table_entry);
}

int	accept(void)
{
	return (1);
}

int	reject(void)
{
	return (-1);
}

/*
1. Returns AST built checking the parsing table (syntax) 
2. Uses shift and reduce method
*/

t_tree	*syntax_analysis(t_token *token, t_table **parsingtable)
{
	t_tree	*tree;
	t_table	*table_entry;
	t_stack	*stack;
	t_token	*input_begin;
	int		i;

	table_entry = NULL;
	stack = init_stack();
	i = 0;
	tree = NULL;
	input_begin = token;
	while (i == 0)
	{
		table_entry = getentry(token, parsingtable, stack);
		if (table_entry != NULL && table_entry->action == SHIFT_TO_STACK)
			i = shift_to_stack(table_entry, &stack, &token);
		else if (table_entry != NULL && table_entry->action == REDUCE_STACK)
			i = reduce_stack(table_entry, &tree, &stack, parsingtable);
		else if (table_entry != NULL && table_entry->action == ACCEPT)
			i = accept();
		else
			i = reject();
	}
	ms_parser_cleaning(&tree, stack, input_begin, i);
	return (ms_fix_param_types(tree));
}
