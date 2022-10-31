/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:03:49 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/31 19:51:32 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*parseblock(char **ps, char *es, t_env *env)
{
	t_cmd	*cmd;

	if (!peek(ps, es, "("))
		print_error("parseblock");
	gettoken(ps, es, 0, env);
	cmd = parseline(ps, es, env);
	if (!peek(ps, es, ")"))
		print_error("syntax - missing )");
	gettoken(ps, es, 0, env);
	cmd = parseredirs(cmd, ps, es, env);
	return (cmd);
}
