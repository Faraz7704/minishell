/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/26 22:41:07 by fkhan            ###   ########.fr       */
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

t_km	*parsekeymap(char **q, char *eq, t_env *env)
{
	char	*key;
	t_list	*keyvalue;

	key = parsekey(*q, eq);
	if (!key)
		return (0);
	*q += ft_strlen(key);
	keyvalue = find_keymap_key(env->kms, key);
	free(key);
	if (!keyvalue)
		return (0);
	return ((t_km *)keyvalue->content);
}

int	expand_size(char *ps, char *es, t_env *env)
{
	int		in_quote;
	int		len;
	t_km	*km;

	len = 0;
	in_quote = 0;
	while (ps < es)
	{
		if (*ps == '\'')
			in_quote = !in_quote;
		else if (!in_quote && *ps == '$')
		{
			ps++;
			if (ft_isalnum(*ps))
			{
				km = parsekeymap(&ps, es, env);
				if (km)
					len += ft_strlen(km->val);
				continue ;
			}
			ps--;
		}
		len++;
		ps++;
	}
	if (in_quote)
		return (-1);
	return (len);
}

void	expand(char *ps, char *es, char **argv, t_env *env)
{
	char	*s;
	char	*new;
	int		in_quote;
	t_km	*km;

	s = ps;
	new = *argv;
	in_quote = 0;
	while (s < es)
	{
		if (*s == '\'')
			in_quote = !in_quote;
		else if (!in_quote && *s == '$')
		{
			s++;
			if (ft_isalnum(*s))
			{
				km = parsekeymap(&s, es, env);
				if (km)
				{
					*new = '\0';
					new += ft_strlcat(new, km->val, ft_strlen(km->val) + 1);
				}
				continue ;
			}
			s--;
		}
		*new = *s;
		s++;
		new++;
	}
	*new = '\0';
}

char	*expandline(char *ps, char *es, t_env *env)
{
	char	*ret;
	int		len;

	len = expand_size(ps, es, env);
	if (len < 0)
	{
		ft_fprintf(2, "syntax - missing '\n");
		exit(1);
	}
	ret = ft_calloc(sizeof(char), (len + 1));
	if (!ret)
		print_error("malloc error\n");
	expand(ps, es, &ret, env);
	return (ret);
}
