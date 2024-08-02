/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:14:16 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/31 02:29:46 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_all(t_envb *env, int ac)
{
	int		i;
	int		j;

	i = 0;
	while (i < env_size(env->env))
	{
		j = i + 1;
		while (j < env_size(env->env))
		{
			if (ft_comp(env->env[i], env->env[j]) > 0)
				ft_swap(&env->env[i], &env->env[j]);
			j++;
		}
		i++;
	}
	if (ac == 1)
		print_all_utils(env);
}

void	print_3(t_envb *env)
{
	if (env->oldpwd)
		printf("declare -x OLDPWD\n");
	if (env->pwd)
		printf("declare -x PWD=\"%s\"\n", env->pwd);
	if (env->shlvl)
		printf("declare -x SHLVL=\"%d\"\n", env->shlvl);
}

void	print_export(t_envb *env, int ac)
{
	int	i;

	i = 0;
	if (!env->env)
		print_3(env);
	else
		print_all(env, ac);
}

int	main_export_utils(t_envb *env, char **av)
{
	int	i;
	int	j;
	int	return_value;
	int	option;

	i = 0;
	while (av[i++])
	{
		option = 0;
		return_value += check_args(av[i]);
		j = -1;
		while (env->env[++j])
		{
			if (!ft_strncmp(env->env[j], av[i], check_export(env->env[j])))
				if (check_export(av[i]))
					option = new_env2(env, j, av[i]);
		}
		if (option == 0)
		{
			env->env[j + 1] = NULL;
			env->env[j] = av[i];
		}
	}
	return (return_value);
}

int	main_export(int ac, char **av, t_envb *env)
{
	int		return_value;
	int	tmp;
	if (ac == 1)
		print_export(env, ac);
	else
		return_value = main_export_utils(env, av);
	if (return_value > 0)
		return_value = 1;
	return (return_value);
}
