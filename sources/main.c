/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:44:41 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/16 19:18:13 by fkhan            ###   ########.fr       */
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

pid_t	fork1(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_error("fork: Resource temporarily unavailable");
	return (pid);
}

char	*ft_first_word(char *str)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	while (str[i] && !ft_strchr(WHITESPACE, str[i]))
		i++;
	len = i;
	new = ft_calloc(sizeof(char), len);
	if (!new)
		print_error("malloc error\n");
	i = 0;
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	ft_chdir(char *path, t_list	*kms)
{
	char	*parse_path;

	if (*path == '~')
	{
		if (chdir(((t_km *)find_keymap_key(kms, "HOME")->content)->val) < 0)
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
	t_list	*kms;

	(void)ac;
	(void)av;
	kms = init_keymaps(env);
	init_fd();
	while (getcmd(&buf) >= 0)
	{
		if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
		{
			ft_chdir(buf + 3, kms);
			continue ;
		}
		runcmd(parsecmd(buf), &kms, env);
		free(buf);
	}
	// rl_clear_history();
	return (0);
}
