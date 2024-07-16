#include "../../minishell.h"

int	check_av_size(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 20)
		return (1);
	if (i > 18)
	{
		if ((str[0] == '-' && ft_strncmp(str, "-9223372036854775809", 21) >= 0)
			|| ft_strncmp(str, "9223372036854775808", 20) >= 0)
			return (1);
		else
			return (0);

	}
	else
		return (0);
}

int	main_exit(int ac, char **av)
{
	if (ac == 1)
	{
		printf("exit\n");
		return (0);
	}
	if (av[1] && (!(av[1][0] >= '0' && av[1][0] <= '9' || (av[1][0] == '+'
		&& (av[1][1] >= '0' && av[1][1] <= '9'))
		|| (av[1][0] == '-' && (av[1][1] >= '0' && av[1][1] <= '9'))))
		|| check_av_size(av[1]) == 1)
	{
		printf("exit\n");
		write(2, "minishell: exit: ", 18);
		write(2, av[1], ft_strlen(av[1]));
		write(2, ": numeric argument required\n", 29);
		exit (255);
	}
	if (ac > 2)
	{
		write(2, "exit\n", 6);
		write(2, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	if (ac == 2)
	{
		printf("exit\n");
		exit (ft_atoi((av[1])) % 256);
	}
	exit (0);
}
