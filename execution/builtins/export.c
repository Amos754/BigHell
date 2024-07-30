/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:14:16 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/30 01:53:44 by marechaloli      ###   ########.fr       */
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

int	main_export_utils(t_envb *env, t_envb *export, char **av)
{
	int	i;
	int	j;
	int	export_value;
	int	return_value;
	int	option;

	i = 0;
	while (av[i++])
	{
		option = 0;
		return_value += check_args(av[i]);
		export_value = check_export(av[i]);
		j = 0;
		while (env->env[j])
		{
			if (!ft_strncmp(env->env[j], av[i], check_export(env->env[j])))
			{
				option = 1;
				if (export_value > 0)
					new_env2(env, export, j, av[i]);
			}
			j++;
		}
		if (!option)
		{
			env->env[j + 1] = NULL;
			env->env[j] = av[i];
		}
	}
	return (return_value);
}

int	main_export(int ac, char **av, t_envb *env)
{
	t_envb	*export;
	int		return_value;
	int	tmp;
	if (ac == 1 || ac == 0)
	{
		print_export(env, ac);
	}
	else
	{
		return_value = main_export_utils(env, export, av);
		// main_export(0, NULL, env);
	}
	if (return_value > 0)
		return_value = 1;
	return (return_value);
}
