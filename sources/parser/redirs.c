/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:04:32 by fkhan             #+#    #+#             */
/*   Updated: 2022/11/22 21:42:59 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_cmd	*go_next(t_cmd *cmd, char **ps, char *es, t_env *env)
{
	int		tok;
	char	*file;

	tok = gettoken(ps, es, &file, env);
	if (tok == -1)
		return (0);
	if (tok != -2)
		free(file);
	cmd = parseredirs(cmd, ps, es, env);
	return (cmd);
}

static t_cmd	*get_redircmd(int tok, t_cmd *cmd, char	*file)
{
	if (tok == '<')
		cmd = redircmd(cmd, file, O_RDONLY, 0);
	else if (tok == '>')
		cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_TRUNC, 1);
	else if (tok == '+')
		cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_APPEND, 1);
	return (cmd);
}

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es, t_env *env)
{
	int		tok;
	char	*file;

	if (!cmd || *ps >= es || peek(ps, es, "|)"))
		return (cmd);
	if (peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, env);
		if (gettoken(ps, es, &file, env) != 'a')
			return (ft_fprintf(1, "syntax error\n"), NULL);
		if (tok == '-')
			cmd = heredoccmd(cmd, ft_strdup("."), file, env);
		cmd = parseredirs(cmd, ps, es, env);
		cmd = get_redircmd(tok, cmd, file);
	}
	else
		cmd = go_next(cmd, ps, es, env);
	return (cmd);
}

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
