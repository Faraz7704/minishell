/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:44:41 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/20 00:22:54 by fkhan            ###   ########.fr       */
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

static int	getcmd(char **buf)
{
	buf[0] = readline(BEGIN(49, 34)"minishell>$"CLOSE);
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

void	ft_chdir(char *path, t_list	*kms)
{
	t_list	*home_km;
	char	*parse_path;

	if (!*path || *path == '~')
	{
		home_km = find_keymap_key(kms, "HOME");
		if (home_km && chdir(((t_km *)home_km->content)->val) < 0)
			ft_fprintf(2, "cd: %s: No such file or directory\n", path);
		return ;
	}
	parse_path = ft_first_word(path);
	if (chdir(parse_path) < 0)
		ft_fprintf(2, "cd: %s: No such file or directory\n", parse_path);
	free(parse_path);
}

int	main(int ac, char **av, char **env)
{
	char	*buf;
	t_env	environment;

	(void)ac;
	(void)av;
	environment.kms = init_keymaps(env);
	environment.env = env;
	init_fd();
	while (getcmd(&buf) >= 0)
	{
		if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
		{
			ft_update_pwd("OLDPWD", &environment);
			ft_chdir(buf + 3, environment.kms);
			ft_update_pwd("PWD", &environment);
			continue ;
		}
		runcmd(parsecmd(buf), &environment);
		free(buf);
	}
	return (0);
}
