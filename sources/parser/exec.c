/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:01:30 by fkhan             #+#    #+#             */
/*   Updated: 2022/11/21 14:28:50 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	parseargv_size(char *ps, char *es, t_env *env)
{
	int		tok;
	int		argc;
	char	*temp;

	argc = 0;
	while (!peek(&ps, es, "|)"))
	{
		if (peek(&ps, es, "<>"))
		{
			gettoken(&ps, es, 0, env);
			gettoken(&ps, es, &temp, env);
			free(temp);
			continue ;
		}
		temp = NULL;
		tok = gettoken(&ps, es, &temp, env);
		if (tok && !*temp)
		{
			free(temp);
			continue ;
		}
		free(temp);
		if (tok == -1)
			return (0);
		if (tok == 0)
			break ;
		if (tok != 'a')
			print_error("syntax");
		argc++;
	}
	return (argc);
}

static void	parseargv(t_execcmd *cmd, char **ps, char *es, t_env *env)
{
	int		tok;
	int		argc;
	char	*temp;

	argc = 0;
	while (!peek(ps, es, "|)"))
	{
		if (peek(ps, es, "<>"))
		{
			gettoken(ps, es, 0, env);
			gettoken(ps, es, &temp, env);
			free(temp);
			continue ;
		}
		tok = gettoken(ps, es, &cmd->argv[argc], env);
		if (tok && !*cmd->argv[argc])
		{
			free(cmd->argv[argc]);
			continue ;
		}
		if (tok == 0)
			break ;
		if (tok != 'a')
			print_error("syntax");
		argc++;
	}
	cmd->argv[argc] = 0;
}

t_cmd	*parseexec(char **ps, char *es, t_env *env)
{
	t_execcmd	*cmd;
	t_cmd		*ret;
	char		*q;
	int			size;

	if (peek(ps, es, "("))
		return (parseblock(ps, es, env));
	ret = execcmd(env);
	cmd = (t_execcmd *)ret;
	q = *ps;
	ret = parseredirs(ret, &q, es, env);
	if (!ret)
	{
		free(cmd);
		*ps = es;
		return (0);
	}
	size = parseargv_size(*ps, es, env);
	if (!size)
	{
		free(cmd);
		*ps = es;
		return (0);
	}
	cmd->argv = (char **)ft_calloc(sizeof(char *), size + 1);
	if (!cmd->argv)
		print_error("malloc error\n");
	parseargv(cmd, ps, es, env);
	return (ret);
}

t_cmd	*execcmd(t_env *env)
{
	t_execcmd	*cmd;

	cmd = ft_calloc(sizeof(*cmd), 1);
	if (!cmd)
		print_error("malloc error");
	cmd->type = EXEC;
	cmd->env = env;
	return ((t_cmd *)cmd);
}
