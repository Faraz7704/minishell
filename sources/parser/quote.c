/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:59:56 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/24 15:36:46 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	quotelen(char *ps, char *es, char *quote)
{
	int		i;
	int		len;
	int		in_quote;

	i = 0;
	len = 0;
	in_quote = 0;
	while (&ps[i] < es)
	{
		if (!in_quote && ft_strchr(QUOTES, ps[i]))
			*quote = ps[i];
		if (ps[i] == *quote)
		{
			in_quote = !in_quote;
			i++;
			continue ;
		}
		if (!in_quote && (ft_strchr(WHITESPACE, ps[i])
				|| ft_strchr(SYMBOLS, ps[i])))
			break ;
		len++;
		i++;
	}
	if (in_quote)
		return (-1);
	return (len);
}

static int	trimquote(char *ps, char *es, char **new, t_env *env)
{
	int		i;
	int		j;
	int		in_quote;
	char	quote;
	t_km	*km;
	char	*temp;

	i = 0;
	j = 0;
	quote = '\0';
	in_quote = 0;
	while (&ps[i] < es)
	{
		if (!in_quote && ft_strchr(QUOTES, ps[i]))
			quote = ps[i];
		if (ps[i] == quote)
		{
			in_quote = !in_quote;
			i++;
			continue ;
		}
		if (!in_quote && (ft_strchr(WHITESPACE, ps[i])
				|| ft_strchr(SYMBOLS, ps[i])))
			break ;
		if ((in_quote && quote != '\'' && ps[i] == '$')
			|| (!in_quote && ps[i] == '$'))
		{
			i++;
			km = expansion(&ps[i], es, env);
			if (km)
			{
				temp = *new;
				*new = ft_strjoin(temp, km->val);
				i += ft_strlen(km->key);
				j += ft_strlen(km->val);
				free(temp);
				continue ;
			}
			if (&ps[i] < es && (ft_isalpha(ps[i]) || !in_quote))
			{
				while (&ps[i] < es && ft_isalpha(ps[i]))
					i++;
				continue ;
			}
			if (ft_isdigit(ps[i]))
			{
				i++;
				continue ;
			}
			i--;
		}
		(*new)[j] = ps[i];
		i++;
		j++;
	}
	(*new)[j] = '\0';
	if (in_quote)
		return (-1);
	return (i);
}

int	parsequote(char *ps, char *es, char **argv, t_env *env)
{
	int		len;
	int		total_len;
	char	*new;
	char	quote;

	quote = '\0';
	len = quotelen(ps, es, &quote);
	if (len < 0)
	{
		ft_fprintf(2, "syntax - missing %c\n", quote);
		exit(1);
	}
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		print_error("malloc error");
	total_len = trimquote(ps, es, &new, env);
	*argv = new;
	return (total_len);
}
