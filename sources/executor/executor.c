/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:59:38 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/04 18:03:44 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(char *cmd, char **argv, t_list *kms)
{
	int		i;

	if (ft_strequals(cmd, "env"))
		print_keymaps(kms);
	else if (ft_strequals(cmd, "pwd"))
	{
		char *str = NULL;
		ft_printf("%s\n", getcwd(str, 1000));
	}
	else if (ft_strequals(cmd, "echo"))
	{
		int	n;
		int	i;

		n = 0;
		i = 1;
		if (ft_strequals(argv[1], "-n"))
		{
			n = 1;
			i = 2;
		}
		while (argv[i] && argv)
		{
			ft_printf("%s ", argv[i]);
			i++;
		}
		if (n == 0)
			ft_printf("\n");
	}
	else if (ft_strequals(cmd, "export"))
	{
		int	i;

		i = 1;
		while (argv[i])
		{
			add_keymap(&kms, argv[i++]);
		}
		if (i == 1)
			print_export(kms);
	}
	else if (ft_strequals(cmd, "unset"))
	{
		int		i;

		i = 1;
		while (argv[i])
		{
			remove_keymap(&kms, argv[i]);
			i++;
		}
	}
	else if (ft_strequals(cmd, "clear"))
		ft_printf("\e[1;1H\e[2J");
	else
	{
		ft_printf("exec %s\n", cmd);
		i = 0;
		while (argv[i])
		{
			ft_printf("arg %s\n", argv[i]);
			i++;
		}
		return (1);
	}
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
