/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:01:33 by szhakypo          #+#    #+#             */
/*   Updated: 2022/11/11 21:36:27 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	check_cmddir(char *cmd)
{
	int	i;

	i = 0;
	while(cmd[i])
	{
		if (cmd[i] == '/')
			return ;
		i++;
	}
	ft_fprintf(2, "%s: command not found\n", cmd);
	exit_app(127);
}

void	ft_execve(char *cmd, char **argv, t_env *env)
{
	char		*path;
	pid_t		p_id;
	int			status;
	struct stat buff;
	int			fstatus;

	update_env(env);
	p_id = ft_fork();
	if (p_id == 0)
	{
		path = full_command_path(cmd, env->env);
		execve(path, argv, env->env);
		fstatus = stat(cmd, &buff);
		// ft_printf("error: %d\n", errno);
		// ft_printf("fstatus: %d\n", fstatus);
		check_cmddir(cmd);
		if (!fstatus)
		{
			if (buff.st_mode & S_IFDIR)
				ft_fprintf(2, "%s: is a directory\n", cmd);
			else
			{
				ft_fprintf(2, "%s: ", cmd);
				perror(NULL);
			}
			exit_app(126);
		}
		ft_fprintf(2, "%s: ", cmd);
		perror(NULL);
		exit_app(127);
	}
	waitpid(p_id, &status, 0);
	if (WEXITSTATUS(status))
		g_appinfo.exit_status = WEXITSTATUS(status);
}