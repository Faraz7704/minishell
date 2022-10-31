/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/31 20:21:03 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*parsekey(char *q, char *eq)
{
	int		i;
	char	*key;

	i = 0;
	if (&q[i] < eq && ft_isdigit(q[i]))
		i++;
	else
	{
		while (&q[i] < eq && ft_isalnum(q[i]))
			i++;
		if (!i)
			return (NULL);
	}
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

// int	expand_size(char *ps, char *es, t_env *env)
// {
// 	int		in_quote;
// 	int		len;
// 	t_km	*km;

// 	len = 0;
// 	in_quote = 0;
// 	while (ps < es)
// 	{
// 		if (*ps == '\'')
// 			in_quote = !in_quote;
// 		else if (!in_quote && *ps == '$')
// 		{
// 			ps++;
// 			if (ps < es && !ft_strchr(WHITESPACE, *ps))
// 			{
// 				km = parsekeymap(&ps, es, env);
// 				if (km)
// 					len += ft_strlen(km->val);
// 				continue ;
// 			}
// 			ps--;
// 		}
// 		len++;
// 		ps++;
// 	}
// 	if (in_quote)
// 		return (-1);
// 	return (len);
// }

// void	expand(char *ps, char *es, char **argv, t_env *env)
// {
// 	char	*new;
// 	int		in_quote;
// 	t_km	*km;

// 	new = *argv;
// 	in_quote = 0;
// 	while (ps < es)
// 	{
// 		if (*ps == '\'')
// 			in_quote = !in_quote;
// 		else if (!in_quote && *ps == '$')
// 		{
// 			ps++;
// 			if (ps < es && !ft_strchr(WHITESPACE, *ps))
// 			{
// 				km = parsekeymap(&ps, es, env);
// 				if (km)
// 				{
// 					*new = '\0';
// 					new += ft_strlcat(new, km->val, ft_strlen(km->val) + 1);
// 				}
// 				continue ;
// 			}
// 			ps--;
// 		}
// 		*new = *ps;
// 		ps++;
// 		new++;
// 	}
// 	*new = '\0';
// }

// char	*expandline(char *ps, char *es, t_env *env)
// {
// 	char	*ret;
// 	int		len;

// 	len = expand_size(ps, es, env);
// 	if (len < 0)
// 	{
// 		ft_fprintf(2, "syntax - missing '\n");
// 		exit(1);
// 	}
// 	ret = ft_calloc(sizeof(char), (len + 1));
// 	if (!ret)
// 		print_error("malloc error\n");
// 	expand(ps, es, &ret, env);
// 	return (ret);
// }

int	expandsize(char **ps, char *es, t_env *env)
{
	t_km	*km;

	(*ps)++;
	if (*ps < es && !ft_strchr(WHITESPACE, **ps))
	{
		km = parsekeymap(ps, es, env);
		if (km)
			return (ft_strlen(km->val));
	}
	return (1);
}

void	expandline(char **ps, char *es, char **argv, t_env *env)
{
	t_km	*km;

	(*ps)++;
	if (*ps < es && !ft_strchr(WHITESPACE, **ps))
	{
		km = parsekeymap(ps, es, env);
		if (km)
		{
			**argv = '\0';
			*argv += ft_strlcat(*argv, km->val, ft_strlen(km->val) + 1);
		}
		return ;
	}
	**argv = *(*ps - 1);
	(*argv)++;
}
