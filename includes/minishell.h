/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:37:26 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/04 13:20:33 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CLOSE "\001\033[0m\002"                 // Закрыть все свойства
# define BLOD  "\001\033[1m\002"                 // Подчеркнуть, жирным шрифтом, выделить
# define BEGIN(x,y) "\001\033["#x";"#y"m\002"    // x: background, y: foreground

# include <stdio.h> // printf, strerror, perror
# include <stdlib.h> // malloc, free, exit, getenv
// write, access, read, close, fork, getcwd, chdir
// unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <unistd.h>
# include <fcntl.h> // open,
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h> // opendir, readdir, closedir
# include <sys/wait.h> //wait, waitpid, wait3, wait4
# include <sys/stat.h> // stat, lstat, fstat
# include <sys/ioctl.h> // ioctl
# include <termios.h> //  tcsetattr, tcgetattr
# include <readline/readline.h> //readline, rl_on_new_line, rl_replace_line
# include <readline/history.h> //rl_clear_history, add_history, rl_redisplay
# include <term.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include "ft_printf.h"
# include "libft.h"

# define WHITESPACE " \t\r\n\v"
# define SYMBOLS "<|>()"

# define MAXARGS 10

enum e_cmd_type {
	EXEC = 0,
	PIPE = 1,
	REDIR = 2,
}	cmd_type;

typedef struct s_cmd
{
	enum e_cmd_type	type;
}	t_cmd;

typedef struct s_execcmd
{
	enum e_cmd_type	type;
	char		*argv[MAXARGS];
	char		*eargv[MAXARGS];
}	t_execcmd;

typedef struct s_pipecmd
{
	enum e_cmd_type	type;
	t_cmd 		*left;
	t_cmd 		*right;
}	t_pipecmd;

typedef struct s_keymap
{
	char			*key;
	char			*val;
	struct s_keymap	*next;
}	t_km;

//typedef struct s_shellinfo
//{
//	t_cmd	*cmd;
//	t_km	*kms;
//}	t_si;

typedef struct s_redircmd
{
	enum e_cmd_type	type;
	t_cmd 		*cmd;
	char		*file;
	char		*efile;
	int			mode;
	int			fd;
}	t_redircmd;



// typedef struct s_cmd
// {
// 	char	*str;
// 	struct s_cmd	*next;
// 	enum e_link_type type;
// }	t_cmd;

// main
int			fork1(void);

// debug
void		print_error(char *s);
void		print_keymaps(t_km *kms);
void		print_export(t_km *kms);

// keymap
t_km		*init_keymaps(char **env);
void		add_keymap(t_km **kms, char *keyvalue);
void		update_keymap(t_km *km, char *keyvalue);
t_km		*find_keymap_key(t_km *kms, char *keyvalue);
void		ft_list_remove_if(t_km **begin_list, char *data_ref, int (*cmp)());

// km_utils
t_km		*km_lstlast(t_km *lst);
void		km_lstadd_back(t_km **lst, t_km *new);

// str_utils
size_t		ft_strclen(char *s, char c);
char		*ft_strldup(char *src, int size);
size_t		ft_strdlen(char **s);
int			ft_strequals(char *s1, char *s2);

#endif