/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:01:30 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/31 20:22:09 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	parseargv(t_execcmd *cmd, char **ps, char *es, t_env *env)
{
	int		tok;
	int		argc;

	argc = 0;
	while (!peek(ps, es, "|)"))
	{
		if (peek(ps, es, "<>"))
		{
			gettoken(ps, es, 0, env);
			gettoken(ps, es, 0, env);
			continue ;
		}
		tok = gettoken(ps, es, &cmd->argv[argc], env);
		if (tok == 0)
			break ;
		if (tok != 'a')
			print_error("syntax");
		argc++;
		if (argc >= MAXARGS)
			print_error("too many args");
	}
	cmd->argv[argc] = 0;
}

t_cmd	*parseexec(char **ps, char *es, t_env *env)
{
	t_execcmd	*cmd;
	t_cmd		*ret;
	char		*q;

	if (peek(ps, es, "("))
		return (parseblock(ps, es, env));
	ret = execcmd(env);
	cmd = (t_execcmd *)ret;
	q = *ps;
	ret = parseredirs(ret, &q, es, env);
	parseargv(cmd, ps, es, env);
	return (ret);
}

t_cmd	*execcmd(t_env *env)
{
	t_execcmd	*cmd;

	cmd = ft_calloc(sizeof(*cmd), 1);
	if (!cmd)
		print_error("malloc error");
	cmd->type = EXEC;
	cmd->env = env;
	return ((t_cmd *)cmd);
}
