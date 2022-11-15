/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:37:26 by fkhan             #+#    #+#             */
/*   Updated: 2022/11/08 15:49:18 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// parser
t_cmd	*parsecmd(char *s, t_env *env);
t_cmd	*parseline(char **ps, char *es, t_env *env);
int		peek(char **ps, char *es, char *toks);

// exec
t_cmd	*parseexec(char **ps, char *es, t_env *env);
t_cmd	*execcmd(t_env *env);

// pipe
t_cmd	*parsepipe(char **ps, char *es, t_env *env);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);

// redirs
t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es, t_env *env);
t_cmd	*redircmd(t_cmd *subcmd, char *file, int mode, int fd);
t_cmd	*heredoccmd(t_cmd *subcmd, char *file, char *delim, t_env *env);

// block
t_cmd	*parseblock(char **ps, char *es, t_env *env);

// quote
void	parsequote(char **ps, char *es, char **argv, t_env *env);

// token
int		gettoken(char **ps, char *es, char **argv, t_env *env);

// expansion
int		expandsize(char **ps, char *es, t_env *env);
void	expandline(char **ps, char *es, char **argv, t_env *env);
char	*expandline_v2(char *ps, char *es, t_env *env);

#endif