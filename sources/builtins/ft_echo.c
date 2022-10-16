/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:01:33 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/16 15:32:46 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **argv)
{
	int	n;
	int	i;

	n = 0;
	i = 1;

	if (ft_strcontains(argv[i], "-n"))
	{
		n = 1;
		i = 2;
	}
	while (argv[i] && argv)
	{
		ft_printf("%s", argv[i]);
		i++;
		if (argv[i])
			ft_printf(" ");

	}
	if (n == 0)
		ft_printf("\n");
}