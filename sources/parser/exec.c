/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:01:30 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/26 18:56:40 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_cmd	*parseargv(t_execcmd *cmd, t_cmd *ret, char **ps, char *es)
{
	int		tok;
	int		argc;

	argc = 0;
	while (!peek(ps, es, "|)"))
	{
		tok = gettoken(ps, es, &cmd->argv[argc]);
		if (tok == 0)
			break ;
		if (tok != 'a')
			print_error("syntax");
		argc++;
		if (argc >= MAXARGS)
			print_error("too many args");
		ret = parseredirs(ret, ps, es);
	}
	cmd->argv[argc] = 0;
	return (ret);
}

t_cmd	*parseexec(char **ps, char *es, t_env *env)
{
	t_execcmd	*cmd;
	t_cmd		*ret;

	if (peek(ps, es, "("))
		return (parseblock(ps, es, env));
	ret = execcmd(env);
	cmd = (t_execcmd *)ret;
	ret = parseredirs(ret, ps, es);
	ret = parseargv(cmd, ret, ps, es);
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
