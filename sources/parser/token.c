/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/11/21 17:41:04 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	redirtoken(char **ps, int *ret)
{
	if (**ps == '<')
	{
		(*ps)++;
		if (**ps == '<')
		{
			*ret = '-';
			(*ps)++;
		}
		return (1);
	}
	if (**ps == '>')
	{
		(*ps)++;
		if (**ps == '>')
		{
			*ret = '+';
			(*ps)++;
		}
		return (1);
	}
	return (0);
}

int	gettoken(char **ps, char *es, char **argv, t_env *env)
{
	int		ret;

	while (*ps < es && ft_strchr(WHITESPACE, **ps))
		(*ps)++;
	ret = **ps;
	if (**ps == '|' || **ps == '(' || **ps == ')')
		(*ps)++;
	else if (!redirtoken(ps, &ret) && **ps)
		ret = parsequote(ps, es, argv, env);
	while (*ps < es && ft_strchr(WHITESPACE, **ps))
		(*ps)++;
	return (ret);
}
