/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/26 22:56:40 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	quotelen(char *ps, char *es, char *quote)
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
		len++;
		ps++;
	}
	if (in_quote)
		return (-1);
	return (len);
}

static void	trimquote(char **ps, char *es, char **argv)
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
		*new = *s;
		s++;
		new++;
	}
	*new = '\0';
	*ps = s;
}

void	parsequote(char **ps, char *es, char **argv)
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
	*argv = ft_calloc(sizeof(char), (len + 1));
	if (!*argv)
		print_error("malloc error");
	trimquote(ps, es, argv);
}
