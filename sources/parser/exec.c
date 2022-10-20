/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:01:30 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/20 16:03:08 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*parseexec(char **ps, char *es)
{
	char		*argv;
	int			tok;
	int			argc;
	t_execcmd	*cmd;
	t_cmd		*ret;

	if (peek(ps, es, "("))
		return (parseblock(ps, es));
	ret = execcmd();
	cmd = (t_execcmd *)ret;
	argc = 0;
	ret = parseredirs(ret, ps, es);
	while (!peek(ps, es, "|)"))
	{
		tok = gettoken(ps, es, &argv);
		if (tok == 0)
			break ;
		if (tok != 'a')
			print_error("syntax");
		cmd->argv[argc] = argv;
		argc++;
		if (argc >= MAXARGS)
			print_error("too many args");
		ret = parseredirs(ret, ps, es);
	}
	cmd->argv[argc] = 0;
	return (ret);
}

t_cmd	*execcmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}
