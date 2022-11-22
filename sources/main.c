/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:44:41 by fkhan             #+#    #+#             */
/*   Updated: 2022/11/21 14:37:01 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"

t_appinfo	g_appinfo;

static void	init_fd(void)
{
	int	fd;

	fd = open("console", O_RDWR);
	while (fd >= 0)
	{
		if (fd >= 2)
			break ;
		fd = open("console", O_RDWR);
	}
}

int	getcmd(char *prefix, char **buf)
{
	buf[0] = readline(prefix);
	if (buf[0] == 0)
		return (-1);
	add_history(buf[0]);
	return (0);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_error("fork: Resource temporarily unavailable");
	return (pid);
}

static void	exit_fd()
{
	int	fd;

	fd = 0;
	while (fd <= 2)
	{
		close(fd);
		fd++;
	}
}

static void	clear_cmd(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	t_redircmd	*redircmd;
	t_pipecmd	*pipecmd;

	if (cmd == 0)
		return ;
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		ft_clearsplit(ecmd->argv);
	}
	else if (cmd->type == REDIR)
	{
		redircmd = (t_redircmd *)cmd;
		clear_cmd(redircmd->cmd);
		free(redircmd->file);
		close(redircmd->fd);
	}
	else if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)cmd;
		clear_cmd(pipecmd->left);
		clear_cmd(pipecmd->right);
	}
	else
		print_error("clear_cmd");
	free(cmd);
}

void	exit_app(int status)
{
	clear_cmd(g_appinfo.cmd);
	g_appinfo.cmd = NULL;
	clear_env(g_appinfo.env);
	exit_fd();
	ft_printf("status: %d\n", status);
	exit(status);
}

void	update_exitstatus()
{
	char	*temp;
	char	*keyvalue;

	temp = ft_itoa(g_appinfo.exit_status);
	keyvalue = ft_strjoin("?=", temp);
	free(temp);
	add_keymap(&g_appinfo.env->kms, keyvalue, 0);
	free(keyvalue);
}

int	main(int ac, char **av, char **env)
{
	char	*buf;

	(void)ac;
	(void)av;
	define_input_signals();
	init_fd();
	g_appinfo.exit_status = 0;
	g_appinfo.env = init_env(env);
	while (getcmd("\33[1;31mಠ_ಠ minishell>$\033[0m ", &buf) >= 0)
	{
		g_appinfo.pipe_out = -1;
		g_appinfo.cmd = parsecmd(buf, g_appinfo.env);
		runcmd(g_appinfo.cmd);
		update_exitstatus();
		free(buf);
		clear_cmd(g_appinfo.cmd);
		g_appinfo.cmd = NULL;
	}
	exit_app(g_appinfo.exit_status);
	return (g_appinfo.exit_status);
}
