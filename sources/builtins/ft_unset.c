/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:28:25 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/05 18:54:13 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_list **kms, char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		remove_keymap(kms, argv[i]);
		i++;
	}
}