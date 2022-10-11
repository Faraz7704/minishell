/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:37:26 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/11 19:39:18 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// parser
t_cmd	*parsecmd(char *s);
t_cmd	*parseline(char **ps, char *es);
int		peek(char **ps, char *es, char *toks);
t_cmd	*parsepipe(char **ps, char *es);
t_cmd	*parseexec(char **ps, char *es);
t_cmd	*parseblock(char **ps, char *es);
t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es);
t_cmd	*nulterminate(t_cmd *cmd);
t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd);
t_cmd	*execcmd(void);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
int		gettoken(char **ps, char *es, char **q, char **eq);
int		check_q_change_val(int q);
char	*check_q_iter(char *s, int *q, char quote);
int		check_q(char *s);
int		parser_argv(char **av);
void	removeChar(char * str, char charToRemmove);
void	del_quots(char **av);

#endif