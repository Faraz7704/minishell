/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:03:49 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/20 16:06:16 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*parseblock(char **ps, char *es)
{
	t_cmd	*cmd;

	if (!peek(ps, es, "("))
		print_error("parseblock");
	gettoken(ps, es, 0);
	cmd = parseline(ps, es);
	if (!peek(ps, es, ")"))
		print_error("syntax - missing )");
	gettoken(ps, es, 0);
	cmd = parseredirs(cmd, ps, es);
	return (cmd);
}
