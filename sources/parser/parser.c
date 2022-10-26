/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:59:38 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/26 22:55:35 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*parsecmd(char *s, t_env *env)
{
	char	*es;
	char	*ps;
	char	*q;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	ps = expandline(s, es, env);
	q = ps;
	es = q + ft_strlen(q);
	cmd = parseline(&q, es, env);
	if (q != es)
	{
		ft_fprintf(2, "leftovers: %s\n", q);
		print_error("syntax");
	}
	free(ps);
	return (cmd);
}

t_cmd	*parseline(char **ps, char *es, t_env *env)
{
	t_cmd	*cmd;

	cmd = parsepipe(ps, es, env);
	return (cmd);
}

int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	*ps = s;
	return (*s && ft_strchr(toks, *s));
}
