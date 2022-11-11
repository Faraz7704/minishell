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

void	ft_execve(char *cmd, char **argv, t_env *env)
{
	char	*path;
	pid_t	p_id;
	int		stat;

	update_env(env);
	path = full_command_path(cmd, env->env);
	p_id = ft_fork();
	if (p_id == 0)
	{
		execve(path, argv, env->env);
		ft_fprintf(2, "%s: command not found\n", cmd);
		exit(127);
	}
	waitpid(p_id, &stat, 0);
	if (WEXITSTATUS(stat))
		g_var = WEXITSTATUS(stat);
}