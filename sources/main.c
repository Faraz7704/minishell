/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:44:41 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/02 19:27:19 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"

// static void	exit_shell(t_si *si)
// {
// 	free(si->cmd);
// 	free(si->kms);
// 	free(si);
// }

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

static int	getcmd(char **buf)
{
	buf[0] = readline(BEGIN(49, 34)"minishell>$"CLOSE);
	if (buf[0] == 0)
		return (-1);
	return (0);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		print_error("fork");
	return (pid);
}

int	main(int ac, char **av, char **env)
{
	char	*buf;
	t_km	*kms;

	(void)ac;
	(void)av;
	kms = init_keymaps(env);
	init_fd();
	while (getcmd(&buf) >= 0)
	{
		if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
		{
			buf[ft_strlen(buf) - 1] = 0;
			if (chdir(buf + 3) < 0)
				ft_fprintf(2, "cannot cd %s\n", buf + 3);
			continue ;
		}
		if (fork1() == 0)
			runcmd(parsecmd(buf), kms);
		wait(0);
	}
	return (0);
}
