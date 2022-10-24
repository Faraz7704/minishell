/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/24 17:33:16 by fkhan            ###   ########.fr       */
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

int	expansion(char **q, char *eq, char **s, char **argv, t_env *env)
{
	char	*key;
	t_list	*keyvalue;
	t_km	*km;
	char	*temp;

	key = parsekey(*q, eq);
	if (!key)
		return (0);
	keyvalue = find_keymap_key(env->kms, key);
	free(key);
	if (!keyvalue)
		return (0);
	km = (t_km *)keyvalue->content;
	temp = *argv;
	*argv = ft_strjoin(*argv, km->val);
	free(temp);
	*q += ft_strlen(km->key);
	*s += ft_strlen(*argv);
	return (1);
}
