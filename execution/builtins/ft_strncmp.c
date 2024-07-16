/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmarech <olmarech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:33:28 by olmarech          #+#    #+#             */
/*   Updated: 2024/03/21 13:54:20 by olmarech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cmpchar(char chr1, char chr2)
{
	if ((unsigned char)chr1 != (unsigned char)chr2)
		return ((unsigned char)chr1 - (unsigned char)chr2);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (cmpchar(s1[i], s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return (cmpchar(s1[i], s2[i]));
	return (0);
}
