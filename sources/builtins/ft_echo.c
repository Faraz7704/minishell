/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:01:33 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/13 20:37:15 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **argv)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	if (ft_strcontains(argv[1], "-n"))
	{
		n = 1;
		i = 2;
	}
	while (argv[i] && argv)
	{
		ft_printf("%s ", argv[i]);
		i++;
	}
	if (n == 0)
		ft_printf("\n");
}