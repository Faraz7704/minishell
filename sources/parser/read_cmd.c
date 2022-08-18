/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:48:29 by szhakypo          #+#    #+#             */
/*   Updated: 2022/08/18 19:22:51 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_cmd(char *cmd)
{
	if (cmd[0] == '\0')
		return (1);
	add_history(cmd);
	if (q_checker(cmd) == 1)
		return (1);
	return (0);
}
