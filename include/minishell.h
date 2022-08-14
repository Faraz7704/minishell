#ifndef MINISHELL_H
# define MINISHELL_H

//# include "../libft/libft.h"
# include <stdio.h> // printf, strerror, perror,
# include <stdlib.h> // malloc, free, exit, getenv,
# include <unistd.h> // write, access, read, close, fork, getcwd, chdir, unlink,  execve, dup, dup2, pipe, isatty, ttyname, ttyslot,
# include <fcntl.h> // open,
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill,
# include <dirent.h> // opendir, readdir, closedir,
# include <sys/wait.h> //wait, waitpid, wait3, wait4,
# include <sys/stat.h> // stat, lstat, fstat,
# include <sys/ioctl.h> // ioctl,
# include <termios.h> //  tcsetattr, tcgetattr,
# include <term.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h> //readline, rl_on_new_line, rl_replace_line
# include <readline/history.h> //rl_clear_history, add_history, rl_redisplay
//# include "printf.h"
//# include "libft.h"

typedef struct s_list
{
	void	*key; //PATH=
	void	*data; //someway/
	struct s_node *next;
}t_list;

typedef	struct s_info
{
	char	**envp; //envairment variabless
	t_list	env_list; // poiter to lsit for compait with env
	int		flg; // flag for chechink; WE NEED TO SOLVE ENV AGAIN;
	char	exit_t;
	int		status;
};
//1. Init;
//2.while(!exit_t)
//	a.ft_readline
//	b.lexer (razbit na tokeny)
//	c.parser
//	d.executer
//3.destruct


#endif