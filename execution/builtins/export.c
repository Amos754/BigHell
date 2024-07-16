#include "../../minishell.h"

int	check_export(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	check_print(char *str)
{
	int	i;
	int	j;

	while (str[i])
		i++;
	j = i;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			if (str[i + 1] == '"' && str[j - 1] == '"')
				return (i);
		i++;
	}
	return (0);
}

int	check_stupid(char *tmp, char stupid)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == stupid)
			return (1);
		i++;
	}
	return (0);
}

void	print_all(t_envb *env)
{
	int		i;
	int		j;
	char	**tmp;
	char	**tmp2;

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
	i = 0;
	while (i < env_size(env->env))
	{
		if (check_export(env->env[i]) > 0)
		{
			tmp = ft_split(env->env[i], '=');
			if (check_stupid(tmp[1], '\n'))
			{
				tmp2 = ft_split(tmp[1], '\n');
				if (check_stupid(tmp[1], '"'))
					printf("declare -x %s=%s\n", tmp[0], tmp2[0]);
				else
					printf("declare -x %s=\"%s\"\n", tmp[0], tmp2[0]);
				freetab(tmp);
				freetab(tmp2);
			}
			else
			{
				if (check_stupid(tmp[1], '"'))
					printf("declare -x %s=%s\n", tmp[0], tmp[1]);
				else
					printf("declare -x %s=\"%s\"\n", tmp[0], tmp[1]);
				freetab(tmp);
			}
		}
		else
			printf("declare -x %s\n", env->env[i]);
		i++;
	}
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

t_envb	*new_env2(t_envb *env, t_envb *export, int j, char *str)
{
	env->env[j] = str;
	return (env);
}

t_envb	*new_export(t_envb *export, char *str)
{
		export->env[39] = str;
		return (export);
}

int	main_export(int ac, char **av, t_envb *env)
{
	t_envb	*export;
	int		i;
	int		j;
	int		return_value;
	int		export_value;

	i = 1;
	if (ac == 1)
		print_export(env);
	else
	{	
		while (av[i])
		{
			return_value += check_args(av[i]);
			export_value = check_export(av[i]);
			j = 0;
			while (env->env[j])
			{
				if (!ft_strncmp(env->env[j], av[i], export_value))
				{
					if (export_value > 0)
						env = new_env2(env, export, j, av[i]);
				}
				j++;
			}
			env->env[j + 1] = NULL;
			av[i] = ft_strjoin(av[i], "\n");
			env->env[j] = av[i];
			i++;
		}
	}	
	if (return_value > 0)
		return_value = 1;
	free(env->pwd);
	free(env);
	return (return_value);
}
