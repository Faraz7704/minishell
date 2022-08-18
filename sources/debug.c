/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:40:37 by fkhan             #+#    #+#             */
/*   Updated: 2022/08/18 18:57:58 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_keymaps(t_km *kms)
{
	t_km	*curr;

	curr = kms;
	while (curr)
	{
		ft_printf("key: %s, val: %s\n", curr->key, curr->val);
		curr = curr->next;
	}
}
