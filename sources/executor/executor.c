/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:59:38 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/16 18:25:32 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"

char	*full_command_path(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	*dir;
	char	*full;

	i = 0;
	while (env[i] && ncompare(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && len_ch(path, ':') > -1)
	{
		dir = str_ndup(path, len_ch(path, ':'));
		full = make_command(dir, cmd);
		free(dir);
		if (access(full, F_OK) == 0)
			return (full);
		free(full);
		path += len_ch(path, ':') + 1;
	}
	return (cmd);
}

int	exec(char *cmd, char **argv, t_list **kms, char **env)
{
	// if (parser_argv(argv) == 1)
	// 	return (1);
	if (ft_strequals(cmd, "env"))
		print_keymaps(*kms);
	else if (ft_strequals(cmd, "pwd"))
		ft_pwd();
	else if (ft_strequals(cmd, "echo"))
		ft_echo(argv);
	else if (ft_strequals(cmd, "export"))
		ft_export(kms, argv);
	else if (ft_strequals(cmd, "unset"))
		ft_unset(kms, argv);
	else if (ft_strequals(cmd, "clear"))
		ft_printf("\e[1;1H\e[2J");
	else if (ft_strequals(cmd, "exit"))
		ft_exit(kms, argv);
	else
	{
		char *path = full_command_path(cmd, env);
		pid_t p_id = fork1();
		if (p_id == 0)
		{
			execve(path, argv, env);
			print_error("Command not found\n");
		}
		waitpid(p_id, NULL, 0);
	}
	return (0);
}

int	runcmd(t_cmd *cmd, t_list **kms, char **env)
{
	int			fd_pipe[2];
	pid_t		p_ids[2];
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
		if (exec(ecmd->argv[0], ecmd->argv, kms, env))
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
		runcmd(rcmd->cmd, kms, env);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		if (pipe(fd_pipe) < 0)
		{
			print_error("pipe");
			return (1);
		}
		p_ids[0] = fork1();
		if (p_ids[0] == 0)
		{
			close(fd_pipe[0]);
			dup2(fd_pipe[1], STDOUT_FILENO);
			runcmd(pcmd->left, kms, env);
			close(fd_pipe[1]);
			exit(0);
		}
		p_ids[1] = fork1();
		if (p_ids[1] == 0)
		{
			close(fd_pipe[1]);
			dup2(fd_pipe[0], STDIN_FILENO);
			runcmd(pcmd->right, kms, env);
			close(fd_pipe[0]);
			exit(0);
		}
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		waitpid(p_ids[0], NULL, 0);
		waitpid(p_ids[1], NULL, 0);
	}
	else
	{
		print_error("runcmd");
		return (1);
	}
	return (0);
}
