#include "../../minishell.h"

int	ft_pwd(void)
{
	char	*pwd;
	char	*buf;
	long	size;

	size = pathconf(".", _PC_PATH_MAX);
	buf = malloc((size_t)size);
	if (!buf)
		return (127);
	pwd = getcwd(buf, size);
	if (pwd == NULL)
		return (127);
	printf("%s\n", pwd);
	free(buf);
	return (0);
}

int	main_pwd(int ac, char **av)
{
	if (!ft_strncmp(av[0], "pwd", 3))
	{
		if (ft_pwd() == 127)
			return (127);
		return (0);
	}
	return (127);
}
