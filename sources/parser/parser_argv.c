/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:53:28 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/15 16:45:57 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "executor.h"

void del_quots(char **av)
{
	int i = 1;
	int z = 0;

	while (av[i])
	{
		z = ft_strlen(av[i]) - 1;	
		if((av[i][0] == 39 && av[i][z] == 39) || (av[i][0] == 34 && av[i][z] == 34))
		{			
			if(av[i][0] == 39)
				removeChar(av[i], 39);
			else
				removeChar(av[i], 34);
		}
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