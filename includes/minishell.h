/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:37:26 by fkhan             #+#    #+#             */
/*   Updated: 2022/08/16 15:09:36 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <term.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h> //readline, rl_on_new_line, rl_replace_line
# include <readline/history.h> //rl_clear_history, add_history, rl_redisplay
# include "ft_printf.h"
# include "libft.h"
# include "parse.h"

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

#endif