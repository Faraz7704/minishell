/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:06:26 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/16 13:57:00 by fkhan            ###   ########.fr       */
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

void removeChar(char * str, char charToRemmove)
{
	int i = 0;
	int j = 0;
    int len = ft_strlen(str);

    while(i < len)
	{
		if(str[i] == charToRemmove)
		{
			j = i;
			while (j < len)
			{
				str[j] = str[j+1];
				j++;
			}
			len--;
			i--;
		}
		i++;
	}
}