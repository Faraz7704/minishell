/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:59:38 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/03 00:47:21 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	exec(char *cmd, char **argv, t_km *kms)
{
	int	i;

	(void)cmd;
	(void)argv;

	if (!ft_strncmp(cmd, "env", 3))
		print_keymaps(kms);
	else if(!ft_strncmp(cmd, "pwd", 3))
	{
		char	*str = NULL;
		
		ft_printf("%s\n", getcwd(str, 1000));
	}
	else if(!ft_strncmp(cmd, "echo", 4))
	{
		int	n;
		int	i;

		n = 0;
		i = 1;
		if ((ft_strncmp(argv[1], "-n", 2) == 0) && argv[1])
		{
			n = 1;
			i = 2;
		}
		while(argv[i] && argv)
		{
			ft_printf("%s ", argv[i]);
			i++;
		}
		if (n == 0)
			ft_printf("\n");
	}
	else if(ft_strncmp(cmd, "export", 6) == 0)
			print_export(kms, argv);
	ft_printf("exec %s\n", cmd);
	i = 0;
	while (argv[i])
	{
		ft_printf("arg %s\n", argv[i]);
		i++;
	}
}

void	runcmd(t_cmd *cmd, t_km *kms)
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
		exec(ecmd->argv[0], ecmd->argv, kms);
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
		runcmd(rcmd->cmd, kms);
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
		print_error("runcmd");
	exit(0);
}
