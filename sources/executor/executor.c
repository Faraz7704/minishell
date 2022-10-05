/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:59:38 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/05 18:48:11 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	exec(char *cmd, char **argv, t_list *kms)
{
	if (ft_strequals(cmd, "env"))
		print_keymaps(kms);
	else if (ft_strequals(cmd, "pwd"))
		ft_pwd();
	else if (ft_strequals(cmd, "echo"))
		ft_echo(argv);
	else if (ft_strequals(cmd, "export"))
		ft_export(&kms, argv);
	else if (ft_strequals(cmd, "unset"))
		ft_unset(&kms, argv);
	else if (ft_strequals(cmd, "clear"))
		ft_printf("\e[1;1H\e[2J");
	else if (ft_strequals(cmd, "exit"))
		ft_exit(&kms, argv);
	return (0);
}

int	runcmd(t_cmd *cmd, t_list *kms)
{
	int			p[2];
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;

	if (cmd == 0)
		return (1);
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (ecmd->argv[0] == 0)
			return (1);
		if (exec(ecmd->argv[0], ecmd->argv, kms))
		{
			ft_fprintf(2, "exec %s failed\n", ecmd->argv[0]);
			return (1);
		}
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode) < 0)
		{
			ft_fprintf(2, "open %s failed\n", rcmd->file);
			return (1);
		}
		runcmd(rcmd->cmd, kms);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		if (pipe(p) < 0)
		{
			print_error("pipe");
			return (1);
		}
		if (fork1() == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left, kms);
		}
		if (fork1() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right, kms);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
	}
	else
	{
		print_error("runcmd");
		return (1);
	}
	return (0);
}
