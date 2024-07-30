/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:35:46 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/26 13:29:43 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Allocate memory space in the heap for collected string
*/
char	*token_str(int token_len, char *line)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (token_len + 1));
	if (!str)
		return (NULL);
	while (i < token_len)
	{
		str[i] = *line;
		i++;
		line++;
	}
	str[i] = '\0';
	return (str);
}

/*
Returns a token created from the string part
*/
t_token	*token_cre(int token_len, char *line, char *exit)
{
	t_token	*token;
	int		q;
	char	*str;

	q = 0;
	token = NULL;
	str = token_str(token_len, line);
	token = token_creation(token_len, str, exit, &q);
	return (token);
}

//Might delete!
void	initial(char *new)
{
	int	i;
	
	i = -1;
	while (++i < 1000)
		new[i] = '\0';
}

t_token	*token_creation(int token_len, char *str, char *exit, int *q)
{
	t_token	*token;
	int		i;
	char	new[1000];
	int		i_new;
	char	*as;

	i_new = 0;
	i = 0;
	token = NULL;
	initial(new);
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			*q = replace_quote((t_varcomb){str, exit}, new, &i, &i_new);
		// else if (str[i] == '$')
		// 	check_env((t_varcomb){str, exit}, new, &i, &i_new);
		else
			new[i_new++] = str[i++];
		new[i_new] = '\0';
	}
	free(str);
	if (!ft_strcmp(new, "\0") && *q == 0)
		return (NULL);
	as = ft_strdup(new);
	token = ft_newtoken(as, *q);
	return (token);
}

/*
Returns singly linked list which has tokens
*/

t_token	*ft_token(char *line, t_sdQuote sdquote, char *exit)
{
	t_token	*token;
	t_token	*all;
	int		token_len;

	token = NULL;
	all = NULL;
	while (*line)
	{
		while (*line != '\0' && (*line == ' ' || *line == '\t'))
			line++;
		token_len = sep_to_sep_len(line, &sdquote);
		if (token_len == 0)
			break ;
		token = token_cre(token_len, line, exit);
		ft_tokenadd_back(&all, token);
		line = line + token_len;
	}
	ft_tokenadd_back(&all, ft_newtoken(NULL, 0));
	if (exit)
		free(exit);
	return (all);
}

/*Might add exit code as an argument in ft_lexer*/

t_token	*ft_lexer(char *line)
{
	t_token		*all;
	int			status;
	char		*exit;
	t_sdQuote	sdquote;

	status = 0;
	exit = ft_itoa(status);
	init_sdquote(&sdquote);
	all = ft_token(line, sdquote, exit);
	return (all);
}
