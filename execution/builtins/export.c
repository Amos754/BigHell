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

void print_all(t_envb *env)
{
	int	i;
	int	j;
	int	size;
	char **envtmp;

	size = env_size(env->env);
	envtmp = malloc((size + 1) * sizeof(char *));
	i = -1;
	while (++i < size)
	{
		envtmp[i] = ft_strdup(env->env[i]);
		if (!envtmp[i])
			return (free_tab(envtmp));
	}
	envtmp[size] = NULL;
	i = -1;
	while (++i < env_size(envtmp))
	{
		j = i;
		while (++j < env_size(envtmp))
			if (ft_comp(envtmp[i], envtmp[j]) > 0)
				ft_swap(&envtmp[i], &envtmp[j]);
	}
	print_all_utils(envtmp);
	free_tab(envtmp);
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

void	print_export(t_envb *env)
{
	int	i;

	i = 0;
	if (!env->env)
		print_3(env);
	else
		print_all(env);
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
		print_export(env);
	else
		return_value = main_export_utils(env, av);
	if (return_value > 0)
		return_value = 1;
	return (return_value);
}
