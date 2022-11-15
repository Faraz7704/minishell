/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:01:33 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/25 02:13:42 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	ft_execve(char *cmd, char **argv, t_env *env)
{
	char	*path;
	pid_t	p_id;

	update_env(env);
	p_id = ft_fork();
	if (p_id == 0)
	{
		path = full_command_path(cmd, env->env);
		execve(path, argv, env->env);
		ft_fprintf(2, "%s: command not found\n", cmd);
		exit_app(1, 0, 0);
	}
	waitpid(p_id, NULL, 0);
}
