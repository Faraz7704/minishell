/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:59:38 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/17 18:16:12 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"

int	exec(char *cmd, char **argv, t_env *env)
{
	// if (parser_argv(argv) == 1)
	// 	return (1);
	if (ft_strequals(cmd, "env"))
		print_keymaps(env->kms);
	else if (ft_strequals(cmd, "pwd"))
		ft_pwd();
	else if (ft_strequals(cmd, "echo"))
		ft_echo(argv);
	else if (ft_strequals(cmd, "export"))
		ft_export(argv, env);
	else if (ft_strequals(cmd, "unset"))
		ft_unset(argv, env);
	else if (ft_strequals(cmd, "clear"))
		ft_printf("\e[1;1H\e[2J");
	else if (ft_strequals(cmd, "exit"))
		ft_exit(argv, env);
	else
	{
		char *path = full_command_path(cmd, env->env);
		pid_t p_id = ft_fork();
		if (p_id == 0)
		{
			execve(path, argv, env->env);
			print_error("Command not found\n");
		}
		waitpid(p_id, NULL, 0);
	}
	return (0);
}

int	run_redircmd(t_cmd *cmd, t_env *env)
{
	t_redircmd	*rcmd;
	int			p_id;

	rcmd = (t_redircmd *)cmd;
	p_id = ft_fork();
	if (p_id == 0)
	{
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode, 0666) < 0)
		{
			if (access(rcmd->file, R_OK | W_OK | X_OK) == -1)
				ft_fprintf(2, "%s: Permission denied\n", rcmd->file);
			else
				ft_fprintf(2, "%s: Open failed\n", rcmd->file);
			exit(1);
		}
		runcmd(rcmd->cmd, env);
		exit(0);
	}
	waitpid(p_id, NULL, 0);
	return (0);
}

int	child_pipecmd(t_cmd *cmd, t_env *env, int *argv)
{
	int	p_id;

	p_id = ft_fork();
	if (p_id == 0)
	{
		close(argv[2]);
		dup2(argv[1], argv[0]);
		runcmd(cmd, env);
		close(argv[1]);
		exit(0);
	}
	return (p_id);
}

int	run_pipecmd(t_cmd *cmd, t_env *env)
{
	t_pipecmd	*pcmd;
	int			fd_pipe[2];
	int			p_ids[2];
	int			fdargs[3];

	pcmd = (t_pipecmd *)cmd;
	if (pipe(fd_pipe) < 0)
		print_error("pipe");
	fdargs[0] = STDOUT_FILENO;
	fdargs[1] = fd_pipe[1];
	fdargs[2] = fd_pipe[0];
	p_ids[0] = child_pipecmd(pcmd->left, env, fdargs);
	fdargs[0] = STDIN_FILENO;
	fdargs[1] = fd_pipe[0];
	fdargs[2] = fd_pipe[1];
	p_ids[1] = child_pipecmd(pcmd->right, env, fdargs);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(p_ids[0], NULL, 0);
	waitpid(p_ids[1], NULL, 0);
	return (0);
}

int	runcmd(t_cmd *cmd, t_env *env)
{
	t_execcmd	*ecmd;

	if (cmd == 0)
		return (1);
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (ecmd->argv[0] == 0)
			return (1);
		if (exec(ecmd->argv[0], ecmd->argv, env))
		{
			ft_fprintf(2, "exec %s failed\n", ecmd->argv[0]);
			return (1);
		}
	}
	else if (cmd->type == REDIR)
		return (run_redircmd(cmd, env));
	else if (cmd->type == PIPE)
		return (run_pipecmd(cmd, env));
	else
		print_error("runcmd");
	return (0);
}
