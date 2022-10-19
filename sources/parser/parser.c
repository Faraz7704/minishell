/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:59:38 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/20 00:11:05 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*parsecmd(char *s)
{
	char	*es;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	cmd = parseline(&s, es);
	if (s != es)
	{
		ft_fprintf(2, "leftovers: %s\n", s);
		print_error("syntax");
	}
	return (cmd);
}

t_cmd	*parseline(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parsepipe(ps, es);
	return (cmd);
}

int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	*ps = s;
	return (*s && ft_strchr(toks, *s));
}

t_cmd	*parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, es);
	if (peek(ps, es, "|"))
	{
		gettoken(ps, es, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return (cmd);
}

t_cmd	*parseexec(char **ps, char *es)
{
	char		*argv;
	int			tok;
	int			argc;
	t_execcmd	*cmd;
	t_cmd		*ret;

	if (peek(ps, es, "("))
		return (parseblock(ps, es));
	ret = execcmd();
	cmd = (t_execcmd *)ret;
	argc = 0;
	ret = parseredirs(ret, ps, es);
	while (!peek(ps, es, "|)"))
	{
		tok = gettoken(ps, es, &argv);
		if (tok == 0)
			break ;
		if (tok != 'a')
			print_error("syntax");
		cmd->argv[argc] = argv;
		argc++;
		if (argc >= MAXARGS)
			print_error("too many args");
		ret = parseredirs(ret, ps, es);
	}
	cmd->argv[argc] = 0;
	return (ret);
}

t_cmd	*parseblock(char **ps, char *es)
{
	t_cmd	*cmd;

	if (!peek(ps, es, "("))
		print_error("parseblock");
	gettoken(ps, es, 0);
	cmd = parseline(ps, es);
	if (!peek(ps, es, ")"))
		print_error("syntax - missing )");
	gettoken(ps, es, 0);
	cmd = parseredirs(cmd, ps, es);
	return (cmd);
}

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es)
{
	int		tok;
	char	*file;

	while (peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0);
		if (gettoken(ps, es, &file) != 'a')
			print_error("missing file for redirection");
		if (tok == '<')
			cmd = redircmd(cmd, file, O_RDONLY, 0);
		else if (tok == '>')
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (tok == '+')
			cmd = redircmd(cmd, file, O_WRONLY | O_CREAT | O_APPEND, 1);
	}
	return (cmd);
}

t_cmd	*redircmd(t_cmd *subcmd, char *file, int mode, int fd)
{
	t_redircmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}

t_cmd	*execcmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

char	*parsequote(char *s, char *eq)
{
	int		i;
	int		j;
	int		len;
	int		flag;
	int		in_quotes;
	char	quote;
	char	*new;

	len = 0;
	i = 0;
	flag = 1;
	in_quotes = 0;
	while (&s[i] < eq)
	{
		if (flag && ft_strchr("\'\"", s[i]))
		{
			quote = s[i];
			flag = 0;
		}
		if (s[i] == quote)
		{
			in_quotes = !in_quotes;
			i++;
			continue ;
		}
		if (!in_quotes && (ft_strchr(WHITESPACE, s[i]) || ft_strchr(SYMBOLS, s[i])))
			break ;
		len++;
		i++;
	}
	if (in_quotes)
	{
		ft_fprintf(2, "syntax - missing %c\n", quote);
		exit(1);
	}
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		print_error("malloc error");
	i = 0;
	j = 0;
	flag = 1;
	in_quotes = 0;
	while (&s[i] < eq)
	{
		if (flag && ft_strchr("\'\"", s[i]))
		{
			quote = s[i];
			flag = 0;
		}
		if (s[i] == quote)
		{
			in_quotes = !in_quotes;
			i++;
			continue ;
		}
		if (!in_quotes && (ft_strchr(WHITESPACE, s[i]) || ft_strchr(SYMBOLS, s[i])))
			break ;
		new[j] = s[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

int gettoken(char **ps, char *es, char **argv)
{
	char	*s;
	int		i;
	int		index;
	int		ret;

	s = *ps;
	i = 0;
	while (&s[i] < es && ft_strchr(WHITESPACE, s[i]))
		i++;
	index = i;
	ret = *s;
	if (s[i] == '|' || s[i] == '(' || s[i] == ')')
		i++;
	else if (s[i] == '<')
	{
		i++;
		if (s[i] == '<')
		{
			ret = '-';
			i++;
		}
	}
	else if (s[i] == '>')
	{
		i++;
		if (s[i] == '>')
		{
			ret = '+';
			i++;
		}
	}
	else if (s[i])
	{
		ret = 'a';
		if (argv)
			*argv = parsequote(&s[i], es);
		while (&s[i] < es && !ft_strchr(WHITESPACE, s[i]) && !ft_strchr(SYMBOLS, s[i]))
			i++;
	}
	if (ret != 'a' && argv)
		*argv = ft_strldup(&s[index], i - index + 1);
	while (&s[i] < es && ft_strchr(WHITESPACE, s[i]))
		i++;
	*ps = &s[i];
	return (ret);
}
