/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:37:26 by fkhan             #+#    #+#             */
/*   Updated: 2022/08/17 20:31:09 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PARSE_H
# define PARSE_H

#define CLOSE "\001\033[0m\002"                 // Закрыть все свойства
#define BLOD  "\001\033[1m\002"                 // Подчеркнуть, жирным шрифтом, выделить
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"    // x: background, y: foreground

typedef struct s_key
{
	char			*key;
	char			*val;
	struct s_key	*next;
}	t_key;

typedef struct s_info
{
	char	*cmd;
}	t_info;

typedef struct	s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}	t_sig;

t_info	*init_env(char **env);
int		size_liness(char **s);
t_key	*init_key(char *env);
int		ft_strclen(char *s, char c);
int		ft_strlob(char *s, char c);
void	list_key_addd(t_key **info, char *env);
void	ftt_lstadd_back(t_key **lst, t_key *new);
t_key	*lstlast(t_key *lst);
int		find_cmd(t_info *cmd);
int		q_checker(char *str);
char	*check_close(char c, int *hm, char *cmd);

//char	*checker_of_quater(char *s);

#endif