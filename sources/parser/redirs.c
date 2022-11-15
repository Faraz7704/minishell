/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:04:32 by fkhan             #+#    #+#             */
/*   Updated: 2022/11/08 18:49:43 by fkhan            ###   ########.fr       */
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
			cmd = redircmd(cmd, file, O_RDONLY, STDIN_FILENO);
		else if (tok == '>')
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
		else if (tok == '+')
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
		else if (tok == '-')
			cmd = heredoccmd(cmd, ft_strdup("."), file, env);
	}
	else
	{
		gettoken(ps, es, 0, env);
		cmd = parseredirs(cmd, ps, es, env);
	}
	return (cmd);
}

t_cmd	*heredoccmd(t_cmd *subcmd, char *file, char *delim, t_env *env)
{
	char		*buf;
	char		*temp;
	static int	pipe_out = -1;
	int			fd_pipe[2];

	if (pipe(fd_pipe) < 0)
		print_error("pipe");
	if (pipe_out >= 0)
		close(pipe_out);
	pipe_out = fd_pipe[0];
	while (1)
	{
		buf = readline("> ");
		if (!buf)
			break ;
		temp = expandline_v2(buf, buf + ft_strlen(buf), env);
		if (ft_strequals(temp, delim))
		{
			free(buf);
			free(temp);
			break ;
		}
		ft_fprintf(fd_pipe[1], "%s\n", temp);
		free(buf);
		free(temp);
	}
	close(fd_pipe[1]);
	free(delim);
	return (redircmd(subcmd, file, O_RDONLY, pipe_out));
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
