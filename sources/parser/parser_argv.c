/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:53:28 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/11 19:41:41 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "executor.h"

void del_quots(char **av)
{
	int i = 0;
	int z = 0;

	while(av[i][z])
		z++;
	while (av[i])
	{
		removeChar(av[i], 39);
		i++;
	}	
}

int	parser_argv(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if(check_q(av[i]) == 1)
		{
			ft_fprintf(2, "QUTST ERROR\n");
			return (1);
		}
		i++;
	}
	del_quots(av);
	return (0);
}