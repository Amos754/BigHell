/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:12:06 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/04 01:58:06 by marechaloli      ###   ########.fr       */
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

int	ft_echo(char **av, int nbr, t_envb *env)
{
	char	*str;
	int		i;

	if (nbr == 0)
		i = 1;
	else
		i = nbr;
	while (av[i])
	{
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
	int	i;
	int	j;
	int	minus;

	i = 1;
	nbr = 0;
	minus = 0;
	if (ac > 1 && !ft_strncmp(av[0], "echo", 4))
	{
		if (!ft_strncmp(av[1], "-n", 2))
		{
			while (av[i] && !ft_strncmp(av[i], "-n", 2))
			{
				j = 1;
				while (av[i][++j])
				{
					if (av[i][j] != 'n')
					{
						minus++;
						break ;
					}
				}

				i++;
			}
			nbr = i - minus;
			if (!av[2])
				return (0);
		}
		if (ft_echo(av, nbr, env) == 127)
			return (127);
		return (0);
	}
	else
		printf("\n");
	return (0);
}
