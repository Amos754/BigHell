#include "minishell.h"

char	*dollar_parsing(char **env, char *option)
{
	int	i;
	option = option + 1;
	i = 0;
	option = ft_strjoin(option, "=");
	while (env[i])
	{
		if (ft_strncmp(env[i], option, ft_strlen(option)))
			return (env[i] + ft_strlen(option));
		i++;
	}
	return (NULL);
}
/*IF RETURN_VALUES == NULL, CONSIDER THAT THERE IS NOT A SECOND ARGUMENT 
EXEMPLE :
echo $HOME 
IF "HOME" EXIST, argc = 2. IT WILL BE PARSED LIKE THIS : "echo /Users/blabla"
IF "HOME" DOESN'T EXIST, args = 1, IT WILL BE PARSED LIKE THIS : "echo"*/