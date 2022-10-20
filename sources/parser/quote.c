/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/20 16:28:37 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parsequote(char *s, char *eq, char **argv)
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
	*argv = new;
	return (i);
}
