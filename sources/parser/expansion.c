/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/24 15:41:22 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*parsekey(char *q, char *eq)
{
	int		i;
	char	*key;

	i = 0;
	while (&q[i] < eq && ft_isalnum(q[i]))
		i++;
	if (!i)
		return (NULL);
	key = ft_strldup(q, i + 1);
	if (!key)
		print_error("malloc error\n");
	return (key);
}

t_km	*expansion(char *q, char *eq, t_env *env)
{
	char	*key;
	t_list	*keyvalue;

	key = parsekey(q, eq);
	if (!key)
		return (NULL);
	keyvalue = find_keymap_key(env->kms, key);
	free(key);
	if (!keyvalue)
		return (NULL);
	return ((t_km *)keyvalue->content);
}
