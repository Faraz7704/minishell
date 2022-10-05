/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:23:00 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/05 18:53:29 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_list **kms, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		add_keymap(kms, argv[i++]);
	}
	if (i == 1)
		print_export(*kms);
}