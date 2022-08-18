/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:37:26 by fkhan             #+#    #+#             */
/*   Updated: 2022/08/18 19:22:39 by fkhan            ###   ########.fr       */
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

enum e_execute_type {
	SIGNAL = 0,
	COMMAND = 1,
};

enum e_link_type {
	L_REDIRECT = 1,
	LL_REDIRECT = 2,
	R_REDIRECT = 3,
	RR_REDIRECT = 4,
	AND = 5,
	OR = 6
};

typedef struct s_option
{
	char	*key;
	char	**data;
}	t_option;

typedef struct s_execute
{
	char				*key;
	char				**data;
	//e_execute_type		type;
	t_option			*options;
	struct s_execute	*next;
	//e_link_type			link_type;
}	t_execute;

typedef struct s_pipeline
{
	struct s_pipeline	*parent;
	t_execute			*pre_executes;
	t_execute			*executes;
	struct s_pipeline	*child;
	//e_link_type			link_type;
}	t_pipeline;

typedef struct s_keymap
{
	char			*key;
	char			*val;
	struct s_keymap	*next;
}	t_km;

typedef struct s_shellinfo
{
	char	*cmd;
	t_km	*kms;
}	t_si;

// keymap
t_km	*init_keymaps(char **env);
void	add_keymap(t_km **kms, char *keyvalue);
void	update_keymap(t_km *km, char *keyvalue);

// km_utils
t_km	*km_lstlast(t_km *lst);
void	km_lstadd_back(t_km **lst, t_km *new);

// str_utils
int		ft_strclen(char *s, char c);
char	*ft_strldup(char *src, int size);
int		ft_strdlen(char **s);

// debug
void	print_keymaps(t_km *kms);

#endif