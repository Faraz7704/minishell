/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:48:29 by szhakypo          #+#    #+#             */
/*   Updated: 2022/08/17 20:42:56 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int	size_liness(char **s)
{
	int	i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	find_cmd(t_info *cmd)
{
	if(cmd->cmd[0] == '\0')
		return (1);
	add_history(cmd->cmd);
	if (q_checker(cmd->cmd) == 1)
		return(1);
	if (strcmp(cmd->cmd, "MUHA"))
		printf("Pidaras\n");

	return (0);
	
}