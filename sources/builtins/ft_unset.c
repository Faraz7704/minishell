/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:28:25 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/06 17:33:28 by fkhan            ###   ########.fr       */
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