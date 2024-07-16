#include "../../minishell.h"

// char	*ft_strnstr(const char *s1, const char *s2, size_t len)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	if (!s2[0])
// 		return ((char *)s1);
// 	while (s1[i] && len > 0)
// 	{
// 		if (s1[i] != '\0')
// 		{
// 			j = 0;
// 			while (s1[i + j] == s2[j] && s1[i + j] && i + j < len && s2[j])
// 				j++;
// 			if (s2[j] == '\0')
// 				return ((char *)(s1 + i));
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

static char	**go_to_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*good_cmd;

	while (*paths)
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		good_cmd = ft_strjoin(*paths, cmd);
		if (access(good_cmd, F_OK | X_OK) == 0)
			return (good_cmd);
		free(good_cmd);
		paths++;
	}
	return (NULL);
}

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;
	char	*tmp;

	paths = go_to_path(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		if (!paths[i])
		{
			free_tab(paths);
			return (NULL);
		}
		free(tmp);
		i++;
	}
	return (paths);
}

int	env_size(char **env)
{
	int	size;

	size = 0;
	while (env[size] != NULL)
		size++;
	return (size);
}