#include "../../minishell.h"

int	ft_env(t_envb *env)
{
	int	i;
	int	j;
	int	env_line;

	if (!env->env)
		return (0);
	while (env->env[env_line])
		env_line++;
	j = 0;
	while (j < env_line - 1)
	{
		i = 0;
		while (env->env[j][i])
		{
			printf("%c", env->env[j][i]);
			if (!env->env[j][i + 1])
				printf("\n");
			i++;
		}
		j++;
		if (j == env_line - 1)
			printf("_=/usr/bin/env\n");
	}
	return (0);
}

int	main_env(int ac, char **av, t_envb *env)
{
	if (!env->env)
		return (127);
	if (ac == 1 && !ft_strncmp(av[0], "env", 3))
	{
		if (ft_env(env) == 127)
			return (127);
		return (0);
	}
	if (ac != 1)
	{
		write(2, "env: ", 5);
		write(2, av[2], ft_strlen(av[2]));
		write(2, "No such file or directory\n", 27);
	}
	return (127);
}
