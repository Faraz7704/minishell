/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:40:37 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/04 16:57:04 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *s)
{
	ft_fprintf(2, "%s\n", s);
	exit(1);
}

void	print_export(t_list *lst)
{
	t_list	*curr;
	t_km	*km;

	curr = lst;
	while (curr)
	{
		km = (t_km *)curr->content;
		if (km->val != NULL)
			ft_printf("declare -x %s=\"%s\"\n", km->key, km->val);
		else
			ft_printf("declare -x %s\n", km->key);
		curr = curr->next;
	}
}

void	print_keymaps(t_list *lst)
{
	t_list	*curr;
	t_km	*km;

	curr = lst;
	while (curr)
	{
		km = (t_km *)curr->content;
		if (km->val != NULL)
			ft_printf("%s=%s\n", km->key, km->val);
		curr = curr->next;
	}
}
