/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/22 21:03:40 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	gettoken(char **ps, char *es, char **argv, t_env *env)
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
		if (!argv)
		{
			while (&s[i] < es && !ft_strchr(WHITESPACE, s[i]) && !ft_strchr(SYMBOLS, s[i]))
				i++;
		}
	}
	if (argv)
		i += parsequote(&s[index], es, argv, env);
	while (&s[i] < es && ft_strchr(WHITESPACE, s[i]))
		i++;
	*ps = &s[i];
	return (ret);
}
