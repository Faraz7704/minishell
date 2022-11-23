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

static void	exit_fd(void)
{
	int	fd;

	fd = 0;
	while (fd <= 2)
	{
		close(fd);
		fd++;
	}
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

void	update_exitstatus(void)
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
