/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:04:32 by fkhan             #+#    #+#             */
/*   Updated: 2022/11/25 17:12:12 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	heredoc(char *delim, t_env *env, int fd_pipe)
{
	char		*buf;
	char		*temp;

	while (1)
	{
		buf = readline("> ");
		if (!buf)
			break ;
		temp = expansion(buf, buf + ft_strlen(buf), env);
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

static void	child_heredoc(t_cmd *subcmd, char *delim, t_env *env, int pipe[2])
{
	signal(SIGINT, &sig_handler_heredoc);
	g_appinfo.cmd = subcmd;
	g_appinfo.pipe_in = pipe[1];
	g_appinfo.delim = delim;
	heredoc(delim, env, pipe[1]);
	close(pipe[0]);
}

t_cmd	*heredoccmd(t_cmd *subcmd, char *file, char *delim, t_env *env)
{
	int			p_id;
	int			stat;
	int			fd_pipe[2];

	if (pipe(fd_pipe) < 0)
		print_error("pipe");
	if (g_appinfo.pipe_out >= 0)
		close(g_appinfo.pipe_out);
	g_appinfo.pipe_out = fd_pipe[0];
	p_id = ft_fork();
	if (p_id == 0)
	{
		free(file);
		child_heredoc(subcmd, delim, env, fd_pipe);
		exit_app(0);
	}
	free(delim);
	close(fd_pipe[1]);
	waitpid(p_id, &stat, 0);
	if (WEXITSTATUS(stat))
	{
		g_appinfo.exit_status = WEXITSTATUS(stat);
		close(fd_pipe[0]);
		g_appinfo.pipe_out = -1;
	}
	return (redircmd(subcmd, file, O_RDONLY, fd_pipe[0]));
}
