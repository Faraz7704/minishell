/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:01:30 by fkhan             #+#    #+#             */
/*   Updated: 2022/11/22 18:37:20 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	peekredir(char **ps, char *es, char **temp, t_env *env)
{
	if (peek(ps, es, "<>"))
	{
		gettoken(ps, es, 0, env);
		gettoken(ps, es, temp, env);
		free(*temp);
		return (1);
	}
	return (0);
}

t_cmd	*clearexec(t_cmd *cmd, char **ps, char *es)
{
	free(cmd);
	*ps = es;
	return (0);
}
