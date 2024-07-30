/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:01 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/30 01:51:02 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	env_size(char **env)
// {
// 	int	size;

// 	size = 0;
// 	while (env[size] != NULL)
// 		size++;
// 	return (size);
// }

t_envb	*change_shlvl(t_envb	*env)
{
	int		i;
	char	**tmp;
	int		nbrtmp;
	char	*tmp2;

	nbrtmp = 0;
	i = 0;
	while (env->env[i])
	{
		if (!ft_strncmp(env->env[i], "SHLVL", 5))
		{
			tmp = ft_split(env->env[i], '=');
			nbrtmp = ft_atoi(tmp[1]);
			env->env[i] = ft_strjoin(tmp[0], "=");
			env->env[i] = ft_strjoin(env->env[i], ft_itoa(nbrtmp + 1));
			env->shlvl = nbrtmp + 1;
			freetab(tmp);
			return (env);
		}
		i++;
	}
	return (env);
}

t_envb	*env_init(char **env)
{
	char	*buff;
	t_envb	*envinit;
	int		i;
	char	*old_pwd;

	if (!env)
		i = 0;
	else
		i = env_size(env);
	envinit = malloc(sizeof(t_envb));
	buff = malloc(1024);
	getcwd(buff, 1024);
	envinit->exstatus = 0;
	if (i > 0)
	{
		envinit->env = env;
		envinit->env[env_size(env) - 1] = "_=/usr/bin/env";
		envinit->env[env_size(env)] = NULL;
		envinit = change_shlvl(envinit);
	}
	i = 0;
	if (!env)
	{
		envinit->env = malloc(sizeof(char **) * 4);
		envinit->env[0] = ft_strjoin("PWD=", buff);
		envinit->env[1] = "SHLVL=1";
		envinit->env[2] = "OLDPWD=";
		envinit->env[3] = NULL;
		envinit->env = NULL;
		envinit->pwd = buff;
		envinit->oldpwd = "OLDPWD";
		envinit->shlvl = 1;
		envinit->usr = NULL;
		envinit->i = 1;
		return (envinit);
	}
	else
	{
		envinit->i = 0;
		while (ft_strncmp(envinit->env[i], "OLDPWD=", 7))
			i++;
		envinit->oldpwd = envinit->env[i];
		envinit->pwd = buff;
	}
	envinit->usr = "_=/usr/bin/env";
	return (envinit);
}
