#include "../../minishell.h"

int	change_pwd(t_envb *env)
{
	int		i;
	char	*buff;
	int		j;

	i = 0;
	while (ft_strncmp(env->env[i], "PWD=", 4))
		i++;
	buff = malloc(1024);
	getcwd(buff, 1024);
	buff = ft_strjoin("PWD=", buff);
	if (env->env[i])
		env->env[i] = buff;
	j = 0;
	while (env->env[j])
	{
		printf("%s\n", env->env[j]);
		j++;
	}
	free(env->pwd);
	free(env->env[i]);
	return (1);
}

int	go_to_directory(char *buff, char *dir, t_envb *env)
{
	char	**totalpath;
	char	*buff2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	totalpath = ft_split(buff, '/');
	while (totalpath[i])
		i++;
	printf("%d\n\n", i);
	j = i + 1;
	i = 0;
	while (i < j)
	{
		if (totalpath[i])
			buff2 = ft_strjoin(buff2, totalpath[i]);
		else
			buff2 = ft_strjoin(buff2, dir);
		buff2 = ft_strjoin(buff2, "/");
		i++;
	}
	printf("buff : %s\n\n", buff2);
	change_pwd(env);
	return (chdir(buff2));
}

int	cd_error(char **av, int nbr)
{
	if (nbr == 1)
	{
		write(2, "minishell: cd: ", 16);
		perror(av[1]);
		return (1);
	}
	else if (nbr == 2)
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		return (1);
	}
	else if (nbr == 3)
		return (1);
	return (0);
}

int	go_home(char **envp, t_envb *env)
{
	int		i;
	char	buff[1024];

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "HOME=", 5))
		{
			if (chdir(envp[i] + 5) == -1)
			{
				write(2, "minishell: cd: ", 16);
				perror(envp[i] + 5);
				change_pwd(env);
				free(env);
				return (3);
			}
			change_pwd(env);
			free(env);
			return (0);
		}
		i++;
	}
	change_pwd(env);
	free(env);
	return (2);
}

char	*get_pwd(char *buff)
{
	buff = malloc(1024);
	buff = getcwd(buff, 1024);
	return (buff);
}

void	change_old_pwd(t_envb *env, char *buff)
{
	int	i;

	i = 0;
	while (ft_strncmp(env->env[i], "OLDPWD=", 7))
		i++;
	buff = ft_strjoin("OLDPWD=", buff);
	if (env->env[i])
		env->env[i] = buff;
}

int	main_cd(int ac, char **av, t_envb *env)
{
	char	*buff2;
	int		return_value;

	buff2 = get_pwd(buff2);
	if (ac == 1)
	{
		change_old_pwd(env, buff2);
		free(buff2);
		return (cd_error(NULL, go_home(env->env, env)));
	}
	else
	{
		change_old_pwd(env, buff2);
		free(buff2);
		if (chdir(av[1]) == -1 && change_pwd(env))
		{
			cd_error(av, 1);
			free(env);
			return (1);
		}
	}
	change_pwd(env);
	free(env);
	return (0);
}
