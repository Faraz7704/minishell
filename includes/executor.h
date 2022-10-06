/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:37:26 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/06 17:35:39 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

int		exec(char *cmd, char **argv, t_list **kms);
int		runcmd(t_cmd *cmd, t_list **kms);


// Builtins

void	ft_echo(char **argv);
void	ft_env(t_list	**kms);
void	ft_exit(t_list **kms, char **argv);
void	ft_export(t_list **kms, char **argv);
void	ft_pwd();
void	ft_unset(t_list **kms, char **argv);

#endif