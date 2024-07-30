/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:12:51 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/17 15:12:52 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_av_size(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 20)
		return (1);
	if (i > 18)
	{
		if ((str[0] == '-' && ft_strncmp(str, "-9223372036854775809", 21) >= 0)
			|| ft_strncmp(str, "9223372036854775808", 20) >= 0)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	main_exit(int ac, char **av)
{
	if (ac == 1)
		return (printf("exit\n"), 0);
	if (av[1] && (!(av[1][0] >= '0' && av[1][0] <= '9' || (av[1][0] == '+'
		&& (av[1][1] >= '0' && av[1][1] <= '9'))
		|| (av[1][0] == '-' && (av[1][1] >= '0' && av[1][1] <= '9'))))
		|| check_av_size(av[1]) == 1)
	{
		write(2, "exit\nminishell: exit: ", 23);
		write(2, av[1], ft_strlen(av[1]));
		write(2, ": numeric argument required\n", 29);
		exit (255);
	}
	if (ac > 2)
	{
		write(2, "exit\nminishell: exit: too many arguments\n", 42);
		return (1);
	}
	if (ac == 2)
	{
		printf("exit\n");
		exit (ft_atoi((av[1])) % 256);
	}
	exit (0);
}
