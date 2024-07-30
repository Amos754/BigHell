/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:09:22 by marechaloli       #+#    #+#             */
/*   Updated: 2024/07/25 00:55:27 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_envb	*new_export(t_envb *export, char *str)
{
	export->env[39] = str;
	return (export);
}

void	check_export_utils(t_envb *env, char **tmp)
{
	char	**tmp2;

	tmp2 = ft_split(tmp[1], '\n');
	if (check_stupid(tmp[1], '"'))
		printf("declare -x %s=%s\n", tmp[0], tmp2[0]);
	else
		printf("declare -x %s=\"%s\"\n", tmp[0], tmp2[0]);
	freetab(tmp);
	freetab(tmp2);
}

int	check_stupid(char *tmp, char stupid)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == stupid)
			return (1);
		i++;
	}
	return (0);
}

int	check_export(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	check_print(char *str)
{
	int	i;
	int	j;

	while (str[i])
		i++;
	j = i;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			if (str[i + 1] == '"' && str[j - 1] == '"')
				return (i);
		i++;
	}
	return (0);
}
