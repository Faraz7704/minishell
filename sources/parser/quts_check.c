/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quts_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:56:48 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/11 17:03:25 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "executor.h"

//helper function for Chek_q()
//changes value of quote flag to oposite
int	check_q_change_val(int q)
{
	if (q == 1)
		return (0);
	else
		return (1);
}

char	*check_q_iter(char *s, int *q, char quote)
{
	if (*s == quote)
	{
		*q = check_q_change_val(*q);
		s++;
		if (*s == quote)
				*q = check_q_change_val(*q);
		while (*s != quote && *s != '\0')
		{
			s++;
			if (*s == quote)
				*q = check_q_change_val(*q);
		}
	}
	return (s);
}

// " = 34   ' = 39
//returns 1 if string have opened quote
int	check_q(char *s)
{
	int	q;

	q = 0;
	while (*s != '\0')
	{
		if (*s == 34 || *s == 39)
			s = check_q_iter(s, &q, *s);
		if (*s == '\0')
			break ;
		s++;
	}
	if (q == 1)
		return (1);
	return (0);
}