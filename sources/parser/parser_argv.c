/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:53:28 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/16 19:31:58 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "executor.h"

void	del_quots(char **av)
{
	int	i;
	int	z;

	i = 1;
	z = 0;
	while (av[i])
	{
		z = ft_strlen(av[i]) - 1;
		if ((av[i][0] == 39 && av[i][z] == 39)
			|| (av[i][0] == 34 && av[i][z] == 34))
		{			
			if (av[i][0] == 39)
				ft_remove_char(av[i], 39);
			else
				ft_remove_char(av[i], 34);
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
		if (check_q(av[i]) == 1)
		{
			ft_fprintf(2, "QUTST ERROR\n");
			return (1);
		}
		i++;
	}
	del_quots(av);
	return (0);
}