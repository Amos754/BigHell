#include "../../minishell.h"

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	ft_comp(char *s1, char *s2)
{
	int	len;

	len = 0;
	while (s1[len] && s1[len] == s2[len])
		len++;
	return (s1[len] - s2[len]);
}

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	check_args(char *av)
{
	if (!(av[0] >= 'a' && av[0] <= 'z')
		&& !(av[0] >= 'A' && av[0] <= 'Z') && av[0] != '_')
	{
		write(2, "minishell: export: `", 20);
		write(2, av, ft_strlen(av));
		write(2, "': not a valid identifier\n", 27);
		return (1);
	}
	return (0);
}

