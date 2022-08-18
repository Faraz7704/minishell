/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:06:26 by szhakypo          #+#    #+#             */
/*   Updated: 2022/08/18 18:21:13 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strclen(char *s, char c)
{
	int	i;

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

int	ft_strdlen(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}