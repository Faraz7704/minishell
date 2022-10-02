/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:59:38 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/02 18:06:43 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	exec(char *argv_start, char **argv)
{
	int	i;

	(void)argv_start;
	(void)argv;
	ft_printf("exec %s\n", argv_start);
	i = 0;
	while (argv[i])
	{
		ft_printf("arg %s\n", argv[i]);
		i++;
	}
}

void	runcmd(t_cmd *cmd)
{
	int			p[2];
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;

	if (cmd == 0)
		exit(1);
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (ecmd->argv[0] == 0)
			exit(1);
		exec(ecmd->argv[0], ecmd->argv);
		ft_fprintf(2, "exec %s failed\n", ecmd->argv[0]);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode) < 0)
		{
			ft_fprintf(2, "open %s failed\n", rcmd->file);
			exit(1);
		}
		runcmd(rcmd->cmd);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		if (pipe(p) < 0)
			print_error("pipe");
		if (fork1() == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left);
		}
		if (fork1() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
	}
	else
		print_error("runcmd");
	exit(0);
}
