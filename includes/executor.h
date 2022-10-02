/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:37:26 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/03 00:25:35 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

void	exec(char *cmd, char **argv, t_km *kms);
void	runcmd(t_cmd *cmd, t_km *kms);

	

#endif