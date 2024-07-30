/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:49:57 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/23 16:25:50 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Counts quotes
*/
int	quote_count(int *i, char *str, t_sdQuote *quote)
{
	if (str[*i] == '\"')
	{
		if (quote->double_q == 2)
			return (0);
		quote->double_q++;
	}
	else if (str[*i] == '\'')
	{
		if (quote->single_q == 2)
			return (0);
		quote->single_q++;
	}
	return (1);
}

/*
Returns quote type
*/
int	check_quote(int *i, char *str)
{
	int			a;
	int			type;
	t_sdQuote	quote;

	a = ft_strlen(str);
	init_sdquote(&quote);
	while (*i < a)
	{
		if (!quote_count(i, str, &quote))
			break ;
		*i = *i + 1;
		if ((type = quote_type(&quote)))
			break ;
	}
	if (type == 1 || type == 2)
		return (type);
	if (quote.type == 2 && quote.double_q != 0 && quote.single_q >= 2)
		return (1);
	else if (quote.double_q >= 2 && quote.single_q != 0 && quote.type == 1)
		return (2);
	return (0);
}

int	quote_type(t_sdQuote *quote)
{
	if (quote->double_q == 1 && quote->type == 0)
		quote->type = 2;
	else if (quote->single_q == 1 && quote->type == 0)
		quote->type = 1;
	if (quote->single_q == 2 && quote->type == 1)
		return (1);
	else if (quote->double_q == 2 && quote->type == 2)
		return (2);
	if (quote->double_q == 2 && quote->single_q == 2)
		return (3);
	return (0);
}

int	sq_dollar(char *str, char sq)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == sq)
		{
			while (str[i] != '\0')
			{
				if (str[i] == sq)
					return (0);
				if (str[i] == '$')
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	replace_double(t_varcomb vc, char *new, int *i_new, t_varquote i)
{
	if ((i.qt == 1 && vc.str[i.a] != '\'')
		|| (i.qt == 2 && vc.str[i.a] != '\"'))
	{
		new[(*i_new)] = vc.str[i.a];
		(*i_new) = (*i_new) + 1;
	}
	else if (i.qt == 2 && vc.str[i.a] == '\"')
	{
		if (check_ds(vc.str, i.a, i.i))
			i.a = check_envvar(vc, new, i_new, i);
	}
	else if (i.qt == 0)
	{
		if (check_ds(vc.str, i.a, i.i))
			i.a = check_envvar(vc, new, i_new, i);
		else
		{
			new[*i_new] = vc.str[i.a];
			(*i_new)++;
		}
	}
	return (i.a);
}
