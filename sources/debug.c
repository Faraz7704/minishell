/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:40:37 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/03 19:58:10 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *s)
{
	ft_fprintf(2, "%s\n", s);
	exit(1);
}

void	print_export(t_km *kms)
{
	t_km	*curr;

	curr = kms;
	while (curr)
	{
		if (curr->val != NULL)
			ft_printf("declare -x %s=\"%s\"\n", curr->key, curr->val);
		else
			ft_printf("declare -x %s\n", curr->key);
		curr = curr->next;
	}
}

void	print_keymaps(t_km *kms)
{
	t_km	*curr;

	curr = kms;
	while (curr)
	{
		if (curr->val != NULL)
			ft_printf("%s=%s\n", curr->key, curr->val);
		curr = curr->next;
	}
}
