/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:47:08 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/19 14:47:19 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_clear_stack(t_stack *stack)
{
	t_stack	*next;

	next = NULL;
	while (stack)
	{
		next = stack->next;
		free(stack->data);
		free(stack);
		stack = next;
	}
}

/*Initialize the stack:
Stack is needed to use the reduce and shift method
Reduces when 
*/

t_stack	*init_stack(void)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->state = 0;
	new->next = NULL;
	new->data = NULL;
	new->type = -1;
	return (new);
}

int	change_stack_state(int next_state, t_stack **stack)
{
	t_stack	*new_stack;

	new_stack = (t_stack *)malloc(sizeof(*new_stack));
	if (!new_stack)
		return (-1);
	new_stack->data = NULL;
	new_stack->state = next_state;
	new_stack->next = *stack;
	*stack = new_stack;
	new_stack->type = -1;
	return (0);
}
