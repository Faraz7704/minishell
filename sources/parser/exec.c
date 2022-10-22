/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:01:30 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/22 23:06:05 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_cmd	*parseargv(t_execcmd *cmd, t_cmd *ret, char **ps, char *es, t_env *env)
{
	int		tok;
	int		argc;
	char	*argv;

	argc = 0;
	while (!peek(ps, es, "|)"))
	{
		tok = gettoken(ps, es, &argv, env);
		if (tok == 0)
			break ;
		if (tok != 'a')
			print_error("syntax");
		cmd->argv[argc] = argv;
		argc++;
		if (argc >= MAXARGS)
			print_error("too many args");
		ret = parseredirs(ret, ps, es, env);
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
	ret = execcmd();
	cmd = (t_execcmd *)ret;
	ret = parseredirs(ret, ps, es, env);
	ret = parseargv(cmd, ret, ps, es, env);
	return (ret);
}

t_cmd	*execcmd(void)
{
	t_execcmd	*cmd;

	cmd = ft_calloc(sizeof(*cmd), 1);
	if (!cmd)
		print_error("malloc error");
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}
