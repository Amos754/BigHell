/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:57:10 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/19 14:50:24 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pop_check(t_stack **red, t_stack *stack)
{
	t_stack	*pop;

	if (*red == NULL)
		*red = stack;
	else
	{
		pop = *red;
		while ((*red)->next)
			*red = (*red)->next;
		(*red)->next = stack;
		*red = pop;
	}
	stack->next = NULL;
}

t_stack	*pop_oper(t_stack **stack, int reduce)
{
	t_stack	*temp;
	t_stack	*red_stack;
	int		i;

	i = 0;
	red_stack = NULL;
	temp = NULL;
	if (stack)
	{
		i = 0;
		while (i < reduce)
		{
			temp = (*stack)->next;
			*stack = temp;
			temp = (*stack)->next;
			pop_check(&red_stack, *stack);
			*stack = temp;
			i++;
		}
	}
	return (red_stack);
}

int	push_reducted(t_stack **stack, int next)
{
	t_stack	*new_red;

	new_red = (t_stack *)malloc(sizeof(*new_red));
	if (!new_red)
		return (-1);
	new_red->data = NULL;
	new_red->next = *stack;
	*stack = new_red;
	new_red->state = -1;
	new_red->type = next;
	return (0);
}

int	pro_red_next_state(t_stack *stack, t_table **parsingtable)
{
	int	i;
	int	state;
	int	next_state;

	state = stack->next->state;
	i = -1;
	while (parsingtable[++i])
	{
		if (parsingtable[i]->state == state)
		{
			if (parsingtable[i]->token_type == stack->type)
				return (parsingtable[i]->next_state);
			else if (parsingtable[i]->token_type == -1)
				next_state = parsingtable[i]->next_state;
		}
	}
	return (next_state);
}

int	reduce_stack(t_table *table_entry, t_tree **tree,
		t_stack **stack, t_table **pt)
{
	t_stack	*pop_stack;
	int		j;

	pop_stack = pop_oper(stack, table_entry->nb_reduce);
	if (pop_stack)
	{
		if (!push_reducted(stack, table_entry->next_state))
		{
			j = pro_red_next_state(*stack, pt);
			if (!change_stack_state(j, stack))
			{
				if (!ms_add_tree(tree, &pop_stack, table_entry->next_state))
				{
					ms_clear_stack(pop_stack);
					return (0);
				}
			}
		}
		ms_clear_stack(pop_stack);
	}
	return (-1);
}
