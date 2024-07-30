/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:48:56 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/23 12:46:09 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalnum(int c)
{
	int	a;

	a = 0;
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		++a;
		return (a);
	}
	else
		return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	strchr_ck(char *str, int temp, int i, char sd)
{
	int	j;

	j = 0;
	while (str[temp] != '\0' && temp <= i)
	{
		if (str[temp] == sd)
			j++;
		temp++;
	}
	if (j == 1)
		return (1);
	return (0);
}

int	check_ds(char *str, int a, int i)
{
	while (str[a] != '\0' && a <= i)
	{
		if (str[a] == '$')
			return (1);
		a++;
	}
	return (0);
}

int	check_env(t_varcomb vc, char *new, int *i, int *i_new)
{
	int	temp;
	int	len_var;

	temp = (*i);
	len_var = 0;
	while (vc.str[temp] != '$')
		temp++;
	if (vc.str[temp + 1])
		len_var = replace_var(vc, temp + 1, new, i_new);
	else
	{
		new[0] = '$';
		new[1] = '\0';
		len_var = 0;
	}
	(*i_new) = ft_strlen(new);
	(*i) = (*i) + len_var + 1;
	return (len_var);
}
