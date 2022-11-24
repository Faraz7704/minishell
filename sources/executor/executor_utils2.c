/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:44:46 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/17 13:25:34 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"

void	child_redircmd(t_redircmd *rcmd)
{
	int		fd_redirect;

	if (ft_strequals(rcmd->file, ".") && rcmd->fd > 2)
	{
		if (g_appinfo.pipe_out == -1)
			exit_app(g_appinfo.exit_status);
		dup2(rcmd->fd, STDIN_FILENO);
		close(rcmd->fd);
		runcmd(rcmd->cmd);
		exit_app(g_appinfo.exit_status);
	}
	close(rcmd->fd);
	fd_redirect = open(rcmd->file, rcmd->mode, 0666);
	if (fd_redirect < 0)
	{
		if (errno == 13)
		{
			ft_fprintf(2, "%s: Permission denied\n", rcmd->file);
			exit_app(1);
		}
		ft_fprintf(2, "%s: No such file or directory\n", rcmd->file);
		exit_app(1);
	}
	runcmd(rcmd->cmd);
	exit_app(g_appinfo.exit_status);
}
