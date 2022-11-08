/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:04:32 by fkhan             #+#    #+#             */
/*   Updated: 2022/11/08 13:50:17 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es, t_env *env)
{
	int		tok;
	char	*file;

	if (*ps >= es || peek(ps, es, "|)"))
		return (cmd);
	if (peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, env);
		if (gettoken(ps, es, &file, env) != 'a')
			print_error("missing file for redirection");
		cmd = parseredirs(cmd, ps, es, env);
		if (tok == '<')
			cmd = redircmd(cmd, file, O_RDONLY, 0);
		else if (tok == '>')
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (tok == '+')
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (tok == '-')
			cmd = redircmd(cmd, file, O_RDONLY, 0);
	}
	else
	{
		gettoken(ps, es, 0, env);
		cmd = parseredirs(cmd, ps, es, env);
	}
	return (cmd);
}

// t_cmd	*heredoc(t_cmd *cmd, char *delim)
// {
// 	cmd = redircmd(cmd, ".tmp", O_RDONLY, 0);
// }

t_cmd	*redircmd(t_cmd *subcmd, char *file, int mode, int fd)
{
	t_redircmd	*cmd;

	cmd = ft_calloc(sizeof(*cmd), 1);
	if (!cmd)
		print_error("malloc error");
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}
