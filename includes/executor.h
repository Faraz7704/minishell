/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:37:26 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/11 20:47:07 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

int		exec(char *cmd, char **argv, t_list **kms, char **env);
int		runcmd(t_cmd *cmd, t_list **kms, char **env);


// Builtins

void	ft_echo(char **argv);
void	ft_env(t_list	**kms);
void	ft_exit(t_list **kms, char **argv);
void	ft_export(t_list **kms, char **argv);
void	ft_pwd();
void	ft_unset(t_list **kms, char **argv);


int		len_ch(char *str, char ch);
int		ncompare(char *str1, char *str2, int n);
char	*make_command(char *path, char *bin);
char	*str_ndup(char *str, unsigned int n);
char	*full_command_path(char *cmd, char **env);
#endif