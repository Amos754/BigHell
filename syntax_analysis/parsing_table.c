/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marechalolivier <marechalolivier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:52:30 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/29 00:12:38 by marechaloli      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Add freeing functions!

/*
From the transition of the table (each line) takes
1. state
2. token type or event (common convention)
3. action to take
4. next state to go
5. number of reduced tokens
*/

t_table	*ft_add_table_line(char **arg_line)
{
	t_table	*table_line;

	if (!arg_line)
		return (NULL);
	table_line = (t_table *)malloc(sizeof(*table_line));
	if (!table_line)
		return (NULL);
	table_line->state = ft_atoi(arg_line[0]);
	table_line->token_type = ft_atoi(arg_line[1]);
	table_line->action = ft_atoi(arg_line[2]);
	table_line->next_state = ft_atoi(arg_line[3]);
	table_line->nb_reduce = ft_atoi(arg_line[4]);
	return (table_line);
}

/*
Takes all the transitions of the table (lines)
*/

static int	free_line_args(char *line, char **args, int code)
{
	char	**begin;

	if (line)
		free(line);
	if (args)
	{
		begin = args;
		while (*args)
		{
			free(*args);
			++args;
		}
		free(begin);
	}
	return (code);
}

int	ft_create_table_state(int fd, t_table **table)
{
	char	*line;
	char	**arg_line;
	int		i;
	int		a;

	i = 0;
	line = NULL;
	a = ft_get_next_line(fd, &line, 0);
	while (a >= 0)
	{
		arg_line = ft_split(line, 9);
		table[i++] = ft_add_table_line(arg_line);
		free_line_args(line, arg_line, 0);
		line = NULL;
		if (a == 0)
			break ;
		if (!table[i])
			return (-1);
		a = ft_get_next_line(fd, &line, 0);
	}
	if (a == -1)
		return (-1);
	return (0);
}

void	ms_free_table(t_table **trans)
{
	t_table	**begin;

	begin = NULL;
	if (trans)
	{
		begin = trans;
		while (*trans)
		{
			free(*trans);
			++trans;
		}
		free(begin);
	}
}

/*
Takes all the data from the AUTOMATON
*/

// char	*new_bison(void)
// {
// 	char	*pwd;
// 	char	*buf;
// 	long	size;

// 	size = pathconf(".", _PC_PATH_MAX);
// 	buf = malloc((size_t)size);
// 	if (!buf)
// 		return (".");
// 	pwd = getcwd(buf, size);
// 	if (pwd == NULL)
// 		return (".");
// 	return (pwd);
// }

t_table	**ft_init_parsing_table(char *path)
{
	t_table	**table;
	int		fd;

	table = (t_table **)malloc(sizeof(*table) * (LINES + 1));
	if (!table)
		return (NULL);
	table[0] = NULL;
	table[LINES] = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ms_free_table(table);
		printf("Test 1");
		return (NULL);
	}
	if (ft_create_table_state(fd, table) == -1)
	{
		ms_free_table(table);
		close (fd);
		printf("Test 2");
		return (NULL);
	}
	close(fd);
	return (table);
}
