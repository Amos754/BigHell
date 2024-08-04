/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:12:59 by marechaloli       #+#    #+#             */
/*   Updated: 2024/08/04 01:56:39 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_all_utils(char **env)
{
	int		i;
	char	**tmp;

	i = -1;
	while (++i < env_size(env))
	{
		if (check_export(env[i]) > 0)
		{
			tmp = ft_split(env[i], '=');
			if (check_stupid(tmp[1], '\n'))
				check_export_utils(env, tmp);
			else
			{
				if (!tmp[1])
					printf("declare -x %s=\"\"\n", tmp[0]);
				else if (check_stupid(tmp[1], '"'))
					printf("declare -x %s=%s\n", tmp[0], tmp[1]);
				else
					printf("declare -x %s=\"%s\"\n", tmp[0], tmp[1]);
				freetab(tmp);
			}
		}
		else
			printf("declare -x %s\n", env[i]);
	}
}

char	*check_wave(char *str)
{
	char	*tmp;

	if (ft_strlen(str) == 1 && !ft_strcmp("~", str))
	{
		return ("$");
	}
	if (str[0] == '~')
	{
		tmp = str + 1;
		return (ft_strjoin("$", tmp));
	}
	return (str);
}

char	*dollar_parse(char *str, t_envb *env)
{
	int	i;
	char	*tmp;

	tmp = str;
	i = 0;
	str = check_wave(str);
	if (ft_strcmp(str, tmp))
		return (str);
	if (ft_strlen(str) == 0)
		return ("$");
	if (!ft_strncmp(str, "?", 1))
		return (ft_itoa(env->exstatus));
	while (env->env[i])
	{
		if (!ft_strncmp(env->env[i], str, env_uti(env->env[i])) && !ft_strncmp(env->env[i], str, ft_strlen(str)))
			return (env->env[i] + ft_strlen(str) + 1);
		i++;
	}
	return (NULL);
}
