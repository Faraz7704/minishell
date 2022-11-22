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

static void	heredoc(char *delim, t_env *env, int fd_pipe)
{
	char		*buf;
	char		*temp;

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
		ft_fprintf(fd_pipe, "%s\n", temp);
		free(buf);
		free(temp);
	}
	close(fd_pipe);
	free(delim);
}

static t_cmd	*heredoccmd(t_cmd *subcmd, char *file, char *delim, t_env *env)
{
	int			p_id;
	int			fd_pipe[2];

	if (pipe(fd_pipe) < 0)
		print_error("pipe");
	if (g_appinfo.pipe_out >= 0)
		close(g_appinfo.pipe_out);
	g_appinfo.pipe_out = fd_pipe[0];
	p_id = ft_fork();
	if (p_id == 0)
	{
		signal(SIGINT, &sig_handler_heredoc);
		g_appinfo.cmd = subcmd;
		heredoc(delim, env, fd_pipe[1]);
		free(file);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		exit_app(0);
	}
	free(delim);
	waitpid(p_id, NULL, 0);
	close(fd_pipe[1]);
	return (redircmd(subcmd, file, O_RDONLY, g_appinfo.pipe_out));
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
		{
			ft_fprintf(1, "syntax error near unexpected token `newline'\n");
			return (0);
		}
		if (tok == '-')
			cmd = heredoccmd(cmd, ft_strdup("."), file, env);
		cmd = parseredirs(cmd, ps, es, env);
		if (tok == '<')
			cmd = redircmd(cmd, file, O_RDONLY, STDIN_FILENO);
		else if (tok == '>')
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
		else if (tok == '+')
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
	}
	else
	{
		tok = gettoken(ps, es, &file, env);
		if (tok == -1)
			return (0);
		if (tok != -2)
			free(file);
		cmd = parseredirs(cmd, ps, es, env);
	}
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
