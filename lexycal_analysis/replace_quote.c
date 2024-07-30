/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:54:43 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/26 13:18:45 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*g_envp = NULL;

int	envvar_len(char *str)
{
	int	i;

	i = 0;
	if (!(*str))
		return (0);
	if (ft_isdigit(str[0]))
		return (1);
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			break ;
	}
	if (i == 0)
		return (-1);
	return (i);
}

int	replace_var_2(char *new, char *newstr, int *i_new, int len)
{
	int	i;

	i = *i_new;
	while (newstr && *newstr)
	{
		new[i] = *newstr;
		newstr++;
		i++;
	}
	new[i] = '\0';
	return (len);
}

int	replace_var_util(char *str, int length, char *new, int *i_new)
{
	int		i;
	char	*newstr;
	char	*string;

	i = -1;
	string = malloc(sizeof(char) * (length + 1));
	if (!string)
		return (0);
	while (++i < length)
		string[i] = str[i];
	string[i] = 0;
	newstr = ft_getenv(string);
	free(string);
	if (newstr)
		replace_var_2(new, newstr, i_new, length);
	return (length);
}

int	replace_var(t_varcomb vc, int index, char *new, int *i_new)
{
	int		length;
	char	*string;

	if (vc.str[index] == '?')
		return (replace_var_2(new, vc.exit, i_new, 1));
	length = envvar_len(vc.str);
	if (!length)
		return (0);
	if (length < 0)
	{
		free(string);
		return (replace_var_2(new, "$", i_new, 0));
	}
	length = replace_var_util(vc.str, length, new, i_new);
	return (length);
}

int	check_envvar(t_varcomb vc, char *new, int *i_new, t_varquote i)
{
	int	temp;
	int	variable_len;

	temp = i.a;
	while (vc.str[i.a] != '\0' && i.a < i.i)
	{
		if (vc.str[i.a] == '$' && vc.str[i.a + 1])
		{
			variable_len = replace_var(vc, i.a + 1, new, i_new);
			*i_new = (int)ft_strlen(new);
			i.a = i.a + variable_len + 1;
		}
		else if ((vc.str[i.a] == '\'' && i.qt == 1 && !strchr_ck(vc.str, temp, i.i, '\''))
				|| (vc.str[i.a] == '\"'
				&& i.qt == 2 && !strchr_ck(vc.str, temp, i.i, '\"')))
			i.a++;
		else
		{
			new[*i_new] = vc.str[i.a];
			i.a++;
			*i_new = *i_new + 1;
		}
	}
	new[(*i_new) + 1] = '\0';
	*i_new = ft_strlen(new);
	return (i.a);
}

/*
Replaces quotes and takes only the input string
Returns whether quote exists or no
*/
int	replace_quote(t_varcomb vc, char *new, int *i, int *i_new)
{
	int	quote;
	int	qt;
	int	a;

	a = *i;
	quote = 0;
	qt = check_quote(i, vc.str);
	if (qt == 1 || qt == 2)
		quote = 1;
	while (a < *i)
	{
		if (quote == 1 && vc.str[a] == '\'')
		{
			if (check_ds(vc.str, a, *i) && !sq_dollar(vc.str, '\''))
				a = check_envvar(vc, new, i_new, (t_varquote){a, *i, qt});
		}
		else
			a = replace_double(vc, new, i_new, (t_varquote){a, *i, qt});
		a++;
	}
	new[(*i_new) + 1] = '\0';
	*i_new = ft_strlen(new);
	return (quote);
}
