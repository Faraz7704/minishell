/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:40:37 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/02 14:20:38 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *s)
{
	ft_fprintf(2, "%s\n", s);
	exit(1);
}

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
