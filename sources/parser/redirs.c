/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:04:32 by fkhan             #+#    #+#             */
/*   Updated: 2022/11/08 18:36:54 by fkhan            ###   ########.fr       */
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
			cmd = heredoc(cmd, ".tmp", file, env);
	}
	else
	{
		gettoken(ps, es, 0, env);
		cmd = parseredirs(cmd, ps, es, env);
	}
	return (cmd);
}

t_cmd	*heredoc(t_cmd *cmd, char *file, char *delim, t_env *env)
{
	char	*buf;
	char	*temp;
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		ft_fprintf(2, "%s: Open failed fro heredoc\n", file);
		exit(1);
	}
	while (1)
	{
		buf = readline("> ");
		if (!buf)
			break ;
		if (ft_strequals(buf, delim))
		{
			free(buf);
			break ;
		}
		temp = expandline_v2(buf, buf + ft_strlen(buf), env);
		ft_fprintf(fd, "%s\n", temp);
		free(buf);
		free(temp);
	}
	close(fd);
	cmd = redircmd(cmd, file, O_RDONLY, 0);
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
