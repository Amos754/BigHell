/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:12:21 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/04 23:46:35 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_envb *env)
{
	int	i;
	int	j;
	int	env_line;

	j = -1;
	while (++j < env_size(env->env))
	{
		if (!ft_strncmp(env->env[j], "_=/usr/bin/env",
				ft_strlen("_=/usr/bin/env")))
			j++;
		if (env->env[j])
		{
			if (!check_export(env->env[j]))
				break ;
			i = 0;
			while (env->env[j][i])
			{
				printf("%c", env->env[j][i]);
				if (!env->env[j][i + 1])
					printf("\n");
				i++;
			}
		}
	}
	printf("_=/usr/bin/env\n");
}

int	main_env(int ac, char **av, t_envb *env)
{
	if (ac == 1 && !ft_strncmp(av[0], "env", 3))
		return (ft_env(env), 0);
	if (ac != 1)
	{
		write(2, "env: ", 5);
		write(2, av[1], ft_strlen(av[1]));
		write(2, " : No such file or directory\n", 30);
	}
	return (127);
}
