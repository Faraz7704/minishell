/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/24 17:32:59 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	quotelen(char *ps, char *es, char *quote)
{
	int		i;
	int		len;
	int		in_quote;

	i = 0;
	len = 0;
	in_quote = 0;
	while (&ps[i] < es)
	{
		if (!in_quote && ft_strchr(QUOTES, ps[i]))
			*quote = ps[i];
		if (ps[i] == *quote)
		{
			in_quote = !in_quote;
			i++;
			continue ;
		}
		if (!in_quote && (ft_strchr(WHITESPACE, ps[i])
				|| ft_strchr(SYMBOLS, ps[i])))
			break ;
		len++;
		i++;
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
			s++;
			if (expansion(&s, es, &new, argv, env))
				continue ;
			if (s < es && (ft_isalpha(*s) || !in_quote))
			{
				while (s < es && ft_isalpha(*s))
					s++;
				continue ;
			}
			if (ft_isdigit(*s))
			{
				s++;
				continue ;
			}
			s--;
		}
		*new = *s;
		s++;
		new++;
	}
	*new = '\0';
	*ps = s;
}

void	parsequote(char **ps, char *es, char **argv, t_env *env)
{
	int		len;
	char	quote;

	quote = '\0';
	len = quotelen(*ps, es, &quote);
	if (len < 0)
	{
		ft_fprintf(2, "syntax - missing %c\n", quote);
		exit(1);
	}
	if (!argv)
	{
		*ps += len;
		return ;
	}
	*argv = malloc(sizeof(char) * (len + 1));
	if (!*argv)
		print_error("malloc error");
	trimquote(ps, es, argv, env);
}
