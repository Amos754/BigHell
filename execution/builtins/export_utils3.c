/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:12:59 by marechaloli       #+#    #+#             */
/*   Updated: 2024/07/31 01:53:58 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_all_utils(t_envb *env)
{
	int		i;
	char	**tmp;

	i = -1;
	while (++i < env_size(env->env))
	{
		if (check_export(env->env[i]) > 0)
		{
			tmp = ft_split(env->env[i], '=');
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
			printf("declare -x %s\n", env->env[i]);
	}
}
