/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:06:26 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/23 20:45:44 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strclen(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	*ft_strldup(char *src, int size)
{
	char	*dst;

	dst = malloc(sizeof(char *) * size);
	if (!dst)
		return (0);
	ft_strlcpy(dst, src, size);
	if (!dst)
		return (0);
	return (dst);
}

size_t	ft_strdlen(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strequals(char *s1, char *s2)
{
	return (s1 && s2 && !ft_strncmp(s1, s2, ft_strlen(s1)));
}

int	ft_strcontains(char *s1, char *s2)
{
	return (s1 && s2 && !ft_strncmp(s1, s2, ft_strlen(s2)));
}
