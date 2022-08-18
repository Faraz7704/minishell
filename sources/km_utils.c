/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   km_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:06:26 by szhakypo          #+#    #+#             */
/*   Updated: 2022/08/18 18:57:21 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_km	*km_lstlast(t_km *lst)
{
	t_km	*next_lst;

	if (!lst)
		return (0);
	next_lst = lst;
	while (next_lst->next)
		next_lst = next_lst->next;
	return (next_lst);
}

void	km_lstadd_back(t_km **lst, t_km *new)
{
	t_km	*last_lst;

	if (!lst[0])
		lst[0] = new;
	else
	{
		last_lst = km_lstlast(lst[0]);
		last_lst->next = new;
	}
}
