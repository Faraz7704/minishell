/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:44:41 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/06 17:35:27 by fkhan            ###   ########.fr       */
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
	add_history(buf[0]);
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
	t_list	*kms;

	(void)ac;
	(void)av;
	kms = init_keymaps(env);
	init_fd();
	while (getcmd(&buf) >= 0)
	{
		if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
		{
			if (ft_strlen(buf) > 3 && buf[3] == '~')
			{
				if (chdir(((t_km *)find_keymap_key(kms, "HOME")->content)->val) < 0)
					ft_fprintf(2, "cannot cd %s\n", buf + 3);
			}
			else
			{
				if (chdir(buf + 3) < 0)
					ft_fprintf(2, "cannot cd %s\n", buf + 3);
			}
			continue ;
		}
		runcmd(parsecmd(buf), &kms);
	}
	return (0);
}
