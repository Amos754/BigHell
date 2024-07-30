/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:12:06 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/27 01:59:05 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env_uti(char *str)
{
	int	size;

	size = 0;
	while (str[size] != '=')
		size++;
	return (size);
}

void	dollar_ech(char *str, t_envb *env)
{
	int	i;

	i = 0;
	if (!ft_strncmp(str, "?", 1))
	{
		printf("%d", env->exstatus);
		return ;
	}
	while (env->env[i])
	{
		if (!ft_strncmp(env->env[i], str, env_uti(env->env[i])))
		{
			printf("%s", env->env[i] + ft_strlen(str) + 1);
			return ;
		}
		i++;
	}
	return ;
}

int	ft_echo(char **av, int nbr, t_envb *env)
{
	char	*str;
	int		i;

	if (nbr == 0)
		i = 1;
	else
		i = 2;
	while (av[i])
	{
		if (!ft_strncmp(av[i], "$", 1))
			dollar_ech(av[i] + 1, env);
		else
			printf("%s", av[i]);
		if (av[i + 1])
			printf(" ");
		i++;
	}
	if (nbr == 0)
		printf("\n");
	return (0);
}

int	main_echo(int ac, char **av, t_envb *env)
{
	int	nbr;

	nbr = 0;
	if (ac > 1 && !ft_strncmp(av[0], "echo", 4))
	{
		if (!ft_strncmp(av[1], "-n", 2))
		{
			nbr = 1;
			if (!av[2])
				return (0);
		}
		if (ft_echo(av, nbr, env) == 127)
			return (127);
		return (0);
	}
	else
		printf("\n");
	return (127);
}
