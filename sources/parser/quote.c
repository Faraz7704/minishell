/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/11/21 14:15:39 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	quotelen(char *ps, char *es, char *quote, t_env *env)
{
	int		len;
	int		in_quote;

	len = 0;
	in_quote = 0;
	while (ps < es)
	{
		if (!in_quote && ft_strchr(QUOTES, *ps))
			*quote = *ps;
		if (*ps == *quote)
		{
			in_quote = !in_quote;
			ps++;
			continue ;
		}
		if (!in_quote && (ft_strchr(WHITESPACE, *ps)
				|| ft_strchr(SYMBOLS, *ps)))
			break ;
		if ((in_quote && *quote != '\'' && *ps == '$')
			|| (!in_quote && *ps == '$'))
		{
			len += expandsize(&ps, es, env);
			continue ;
		}
		len++;
		ps++;
	}
	if (in_quote)
		return (-1);
	return (len);
}

static void	trimquote(char **ps, char *es, char **argv, t_env *env)
{
	char	*s;
	char	*new;
	int		in_quote;
	char	quote;

	s = *ps;
	quote = '\0';
	in_quote = 0;
	new = *argv;
	while (s < es)
	{
		if (!in_quote && ft_strchr(QUOTES, *s))
			quote = *s;
		if (*s == quote)
		{
			in_quote = !in_quote;
			s++;
			continue ;
		}
		if (!in_quote && (ft_strchr(WHITESPACE, *s)
				|| ft_strchr(SYMBOLS, *s)))
			break ;
		if ((in_quote && quote != '\'' && *s == '$')
			|| (!in_quote && *s == '$'))
		{
			expandline(&s, es, &new, env);
			continue ;
		}
		*new = *s;
		s++;
		new++;
	}
	*new = '\0';
	*ps = s;
}

int	parsequote(char **ps, char *es, char **argv, t_env *env)
{
	int		len;
	char	quote;

	quote = '\0';
	if (!argv)
	{
		while ((*ps) < es && !ft_strchr(WHITESPACE, **ps)
			&& !ft_strchr(SYMBOLS, **ps))
				(*ps)++;
		return (0);
	}
	len = quotelen(*ps, es, &quote, env);
	if (len < 0)
	{
		ft_fprintf(2, "syntax - missing %c\n", quote);
		return (1);
	}
	*argv = ft_calloc(sizeof(char), (len + 1));
	if (!*argv)
		print_error("malloc error");
	trimquote(ps, es, argv, env);
	return (0);
}
