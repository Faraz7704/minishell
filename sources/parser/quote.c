/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/11/21 18:05:12 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	checkquote(char **ps, char *quote, int *in_quote)
{
	if (!*in_quote && ft_strchr(QUOTES, **ps))
		*quote = **ps;
	if (**ps == *quote)
	{
		*in_quote = !(*in_quote);
		(*ps)++;
		return (1);
	}
	if (!*in_quote && (ft_strchr(WHITESPACE, **ps)
			|| ft_strchr(SYMBOLS, **ps)))
		return (-1);
	return (0);
}

static int	quotelen(char *ps, char *es, char *quote, t_env *env)
{
	int		len;
	int		in_quote;
	int		stat;

	len = 0;
	in_quote = 0;
	while (ps < es)
	{
		stat = checkquote(&ps, quote, &in_quote);
		if (stat == 1)
			continue ;
		if (stat == -1)
			break ;
		if ((in_quote && *quote != '\'' && *ps == '$')
			|| (!in_quote && *ps == '$'))
		{
			len += expandsize(&ps, es, in_quote, env);
			continue ;
		}
		len++;
		ps++;
	}
	if (in_quote)
		return (-1);
	return (len);
}

static void	trimquote(char **ps, char *es, char *argv, t_env *env)
{
	char	quote;
	int		in_q;
	int		stat;

	quote = '\0';
	in_q = 0;
	while (*ps < es)
	{
		stat = checkquote(ps, &quote, &in_q);
		if (stat == 1)
			continue ;
		if (stat == -1)
			break ;
		if ((in_q && quote != '\'' && **ps == '$') || (!in_q && **ps == '$'))
		{
			if (!expandline(ps, es, &argv, env) || !in_q)
				continue ;
			(*ps)--;
		}
		*argv = **ps;
		(*ps)++;
		argv++;
	}
	*argv = '\0';
}

int	parsequote(char **ps, char *es, char **argv, t_env *env)
{
	int		len;
	char	quote;

	quote = '\0';
	len = quotelen(*ps, es, &quote, env);
	if (!argv || (len == 0 && !quote))
	{
		while ((*ps) < es && !ft_strchr(WHITESPACE, **ps)
			&& !ft_strchr(SYMBOLS, **ps))
				(*ps)++;
		return (-2);
	}
	if (len < 0)
	{
		ft_fprintf(2, "syntax - missing %c\n", quote);
		return (-1);
	}
	*argv = ft_calloc(sizeof(char), (len + 1));
	if (!*argv)
		print_error("malloc error");
	trimquote(ps, es, *argv, env);
	return ('a');
}
