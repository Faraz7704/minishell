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
		if (fd >= 3)
		{
			close(fd);
			break ;
		}
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

int	main(int ac, char **av, char **env)
{
	char	*buf;
	t_env	*m_env;

	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	init_fd();
	m_env = init_env(env);
	while (getcmd("\33[1;31mಠ_ಠ minishell>$\033[0m ", &buf) >= 0)
	{
		runcmd(parsecmd(buf, m_env));
		free(buf);
	}
	clear_env(m_env);
	return (0);
}
