/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:37:26 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/17 23:20:52 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

// executor
int		exec(char *cmd, char **argv, t_env *env);
int		runcmd(t_cmd *cmd, t_env *env);

// builtins
void	ft_echo(char **argv);
void	ft_env(t_env *env);
void	ft_exit(char **argv, t_env *env);
void	ft_export(char **argv, t_env *env);
void	ft_pwd(void);
char	*ft_get_pwd(void);
char	*ft_add_pwd(char *key, t_env *env);
void	ft_unset(char **argv, t_env *env);

// executor_utils
int		len_ch(char *str, char ch);
int		ncompare(char *str1, char *str2, int n);
char	*make_command(char *path, char *bin);
char	*str_ndup(char *str, unsigned int n);
char	*full_command_path(char *cmd, char **env);
unsigned long long		ft_atoull(char *str, int *minus);

#endif