/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:12:06 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/05 00:04:23 by marechaloli      ###   ########.fr       */
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

int	check_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	nbr_value(char **av)
{
	int	i;
	int	j;
	int	minus;

	i = 1;
	minus = 0;
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
	return (i - minus);
}

int	main_echo(int ac, char **av, t_envb *env)
{
	int	nbr;

	nbr = 0;
	if (ac > 1 && !ft_strncmp(av[0], "echo", 4))
	{
		if (!ft_strncmp(av[1], "-n", 2) && !check_n(av[1] + 1))
		{
			nbr = nbr_value(av);
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
