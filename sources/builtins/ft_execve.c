/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:01:33 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/20 15:58:54 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	ft_execve(char *cmd, char **argv, t_env *env)
{
	char	*path;
	pid_t	p_id;
	int		ret;

	path = full_command_path(cmd, env->env);
	p_id = ft_fork();
	ret = 0;
	if (p_id == 0)
	{
		ret = execve(path, argv, env->env);
		print_error("Command not found\n");
	}
	waitpid(p_id, NULL, 0);
	return (ret);
}
