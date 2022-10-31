/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:37:26 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/31 19:38:06 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
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

# define WHITESPACE " \t\r\n\v\f"
# define SYMBOLS "<|>()"
# define QUOTES "\'\""

# define MAXARGS 10

enum e_cmd_type {
	EXEC = 0,
	PIPE = 1,
	REDIR = 2,
}	cmd_type;

typedef struct s_env
{
	t_list	*kms;
	char	**env;
}	t_env;

typedef struct s_cmd
{
	enum e_cmd_type	type;
	t_env			*env;
}	t_cmd;

typedef struct s_execcmd
{
	enum e_cmd_type	type;
	t_env			*env;
	char			*argv[MAXARGS];
}	t_execcmd;

typedef struct s_pipecmd
{
	enum e_cmd_type	type;
	t_cmd			*left;
	t_cmd			*right;
}	t_pipecmd;

typedef struct s_redircmd
{
	enum e_cmd_type	type;
	t_cmd			*cmd;
	char			*file;
	int				mode;
	int				fd;
}	t_redircmd;

typedef struct s_keymap
{
	char			*key;
	char			*val;
}	t_km;

// main
pid_t		ft_fork(void);
int			getcmd(char *prefix, char **buf);

// debug
void		print_error(char *s);
void		print_keymaps(t_list *lst);
void		print_export(t_list *lst);
void		print_env(t_list *lst);
void		print_strsplit(char **split);

// keymap
char		*mergekeymap(t_km *km);
void		add_keymap(t_list **lst, char *keyvalue);
void		update_keymap(t_km *km, char *keyvalue);
t_list		*find_keymap_key(t_list *lst, char *keyvalue);
void		remove_keymap(t_list **lst, char *key);

// env
t_env		*init_env(char **env);
char		**ft_getenv(t_list *lst);
void		update_env(t_env *env);
void		clear_env(t_env *env);

// sort_list
t_list		*sort_keymap_alpha(t_list *lst);

// str_utils
size_t		ft_strclen(char *s, char c);
char		*ft_strldup(char *src, int size);
size_t		ft_strdlen(char **s);
int			ft_strequals(char *s1, char *s2);
int			ft_strcontains(char *s1, char *s2);

// str_utils2
char		*ft_first_word(char *str);
void		ft_remove_char(char *str, char c);

// list_utils
void		ft_lstdel(void *content);

//signals
void		sig_handler(int sig_num);
void		ctrl_c(int sig);
int			ctrl_d(void);
void		sig_handler_heredoc(int sig_num);

#endif