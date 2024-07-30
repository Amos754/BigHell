/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:31:11 by abolor-e          #+#    #+#             */
/*   Updated: 2024/07/23 14:11:31 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gnl.h"
#include "../minishell.h"

void	prep_for_next_line(t_list **list)
{
	t_list	*last_node;
	t_list	*new_node;
	char	*str;
	int		i;
	int		a;

	a = 0;
	i = 0;
	str = malloc(BUFFER_SIZE + 1);
	last_node = ft_lstlast(*list);
	new_node = malloc(sizeof(t_list));
	if (!new_node || !str)
		return ;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		str[a++] = last_node->str_buf[i];
	str[a] = '\0';
	new_node->str_buf = str;
	new_node->next = NULL;
	free_list(list, new_node, str);
}

char	*get_until_newline(t_list *list)
{
	char	*new_str;
	int		str_len;

	if (!list)
		return (NULL);
	str_len = len_until_newline(list);
	new_str = malloc(str_len + 1);
	if (!new_str)
		return (NULL);
	copy(list, new_str);
	return (new_str);
}

void	include_list(t_list **list, char *res)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	last_node = ft_lstlast(*list);
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = res;
	new_node->next = NULL;
}

int	create_buffer_list(t_list **list, int fd)
{
	char	*res;
	int		char_read;

	while (!newline_check_list(*list))
	{
		res = malloc(BUFFER_SIZE + 1);
		if (!res)
			return (-1);
		char_read = read(fd, res, BUFFER_SIZE);
		if (char_read == 0 || char_read == -1)
		{
			free(res);
			if (list)
				free_list(list, NULL, NULL);
			return (char_read);
		}
		res[char_read] = '\0';
		include_list(list, res);
	}
	return (char_read);
}

int	ft_get_next_line(int fd, char **next_line, int to_free)
{
	static t_list	*list = NULL;
	int				i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	i = create_buffer_list(&list, fd);
	if (i == 0 || i == -1)
		return (i);
	if (list == NULL)
		return (-1);
	*next_line = get_until_newline(list);
	if (!(*next_line))
	{
		free_list(&list, NULL, NULL);
		return (0);
	}
	prep_for_next_line(&list);
	return (1);
}
