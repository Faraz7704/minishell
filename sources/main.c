/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:44:41 by fkhan             #+#    #+#             */
/*   Updated: 2022/11/08 13:06:01 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"

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

void	exit_app(int code, t_cmd *cmd, t_env *env)
{
	static t_cmd	*m_cmd = NULL;
	static t_env	*m_env = NULL;

	if (code == -1)
	{
		m_cmd = cmd;
		m_env = env;
		return ;
	}
	clear_cmd(m_cmd);
	clear_env(m_env);
	exit_fd();
	exit(code);
}

int	main(int ac, char **av, char **env)
{
	char	*buf;
	t_env	*m_env;
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	init_fd();
	m_env = init_env(env);
	while (getcmd("\33[1;31mಠ_ಠ minishell>$\033[0m ", &buf) >= 0)
	{
		cmd = parsecmd(buf, m_env);
		exit_app(-1, cmd, m_env);
		runcmd(cmd);
		free(buf);
	}
	// rl_clear_history();
	exit_app(0, 0, 0);
	return (0);
}
