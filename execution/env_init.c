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

	i = env_size(env);
	envinit = malloc(sizeof(t_envb));
	buff = malloc(1024);
	getcwd(buff, 1024);
	if (i > 0)
	{
		envinit->env = env;
		envinit->env[env_size(env) - 1] = "_=/usr/bin/env";
		envinit->env[env_size(env)] = NULL;
		envinit = change_shlvl(envinit);
	}
	envinit->oldpwd = "OLDPWD";
	envinit->pwd = buff;
	envinit->usr = "_=/usr/bin/env";
	return (envinit);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_env	*env;
// 	int		i;

// 	i = 0;
// 	env = env_init(envp);
// 	printf("PWD=%s\n", env->pwd);
// 	printf("SHLVL=%d\n", env->shlvl);
// 	printf("%s\n", env->usr);
// 	while (env->env[i])
// 	{
// 		printf("%s\n", env->env[i]);
// 		i++;
// 	}
// 	free(env->pwd);
// 	free(env);
// 	return (0);
// }
