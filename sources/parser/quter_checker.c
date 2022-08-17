/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quter_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:52:00 by szhakypo          #+#    #+#             */
/*   Updated: 2022/08/17 20:27:43 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"

int		q_change_val(int q)
{
	if(q == 1)
		return (0);
	return (1);
}

char	*check_close(char c, int *hm, char *cmd)
{
	if(*cmd == c)
	{
		*hm= q_change_val(*hm);
		cmd++;
		if(*cmd == c)
			*hm = q_change_val(*hm);
		while (*cmd != c && *cmd)
		{
			cmd++;
			if(*cmd == c)
				*hm = q_change_val(*hm);
		}
	}
	return (cmd);
}

int	q_checker(char *str)
{
	int	q;
	int	i;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			check_close(str[i], &q, str);
		i++;
	}
	if (q == 1)
		return(1);
	return (0);
}