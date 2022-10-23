/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/23 20:45:13 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*parsekey(char *q, char *eq, t_env *env)
{
	char	*s;
	char	*key;
	int		len;
	t_list	*keyvalue;

	s = q;
	len = 0;
	while (s < eq && ft_isalnum(*s))
	{
		len++;
		s++;
	}
	if (!len)
		return (NULL);
	key = ft_strldup(q, len + 1);
	if (!key)
		print_error("malloc error\n");
	free(key);
	return ((t_km *)keyvalue->content);
}

t_km	*expansion(char *q, char *eq, t_env *env)
{
	char	*s;
	char	*key;
	int		len;
	t_list	*keyvalue;

	s = q;
	len = 0;
	while (s < eq && ft_isalnum(*s))
	{
		len++;
		s++;
	}
	if (!len)
		return (NULL);
	key = ft_strldup(q, len + 1);
	if (!key)
		print_error("syntax");
	keyvalue = find_keymap_key(env->kms, key);
	if (!keyvalue)
	{
		free(key);
		return (NULL);
	}
	free(key);
	return ((t_km *)keyvalue->content);
}
