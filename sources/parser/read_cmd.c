/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:48:29 by szhakypo          #+#    #+#             */
/*   Updated: 2022/09/30 19:00:41 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_cmd(char *cmd)
{
	init_cmd_list(cmd);
	if (cmd[0] == '\0')
		return (1);
	add_history(cmd);
	if (q_checker(cmd) == 1)
		return (1);
	return (0);
}
