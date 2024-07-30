/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:16:17 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/26 13:08:06 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_envb	*new_env(t_envb *env, int nbr)
{
	while (env->env[nbr])
	{
		env->env[nbr] = env->env[nbr + 1];
		nbr++;
	}
	return (env);
}

int	check_argsu(char *av)
{
	if (!(av[0] >= 'a' && av[0] <= 'z')
		&& !(av[0] >= 'A' && av[0] <= 'Z') && av[0] != '_')
	{
		write(2, "minishell: unset: `", 20);
		write(2, av, ft_strlen(av));
		write(2, "': not a valid identifier\n", 27);
		return (1);
	}
	return (0);
}

int	main_unset(int ac, char **av, t_envb *env)
{
	int		i;
	int		j;
	int		return_value;

	i = 1;
	while (av[i])
	{
		return_value += check_argsu(av[i]);
		j = 0;
		while (env->env[j])
		{
			if (!ft_strncmp(env->env[j], av[i], ft_strlen(av[i])))
				env = new_env(env, j);
			j++;
		}
		i++;
	}
	if (return_value > 0)
		return_value = 1;
	free(env->pwd);
	return (return_value);
}
