/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/26 18:54:56 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	gettoken(char **ps, char *es, char **argv)
{
	int		ret;

	while (*ps < es && ft_strchr(WHITESPACE, **ps))
		(*ps)++;
	ret = **ps;
	if (**ps == '|' || **ps == '(' || **ps == ')' || **ps == '<' || **ps == '>')
	{
		(*ps)++;
		if (**ps == '<')
		{
			ret = '-';
			(*ps)++;
		}
		else if (**ps == '>')
		{
			ret = '+';
			(*ps)++;
		}
	}
	else if (**ps)
	{
		ret = 'a';
		parsequote(ps, es, argv);
	}
	while (*ps < es && ft_strchr(WHITESPACE, **ps))
		(*ps)++;
	return (ret);
}
