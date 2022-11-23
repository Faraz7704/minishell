/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:06:26 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/05 19:40:09 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_strgreater(char *s1, char *s2)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	while (i < len && s2[i])
	{
		if (s2[i] > s1[i])
			return (1);
		if (s2[i] < s1[i])
			return (0);
		i++;
	}
	return (ft_strlen(s2) > len);
}

static void	swap_keymap(t_list **lst, t_km *km, t_list *prev, t_list *curr)
{
	if (!prev)
	{
		lst[0] = ft_lstnew(km);
		lst[0]->next = curr;
	}
	else
	{
		prev->next = ft_lstnew(km);
		prev->next->next = curr;
	}
}

static void	insert_keymap_alpha(t_list **lst, t_km *km)
{
	t_list	*curr;
	t_list	*prev;
	t_km	*km_curr;

	curr = lst[0];
	prev = NULL;
	while (curr)
	{
		km_curr = (t_km *)curr->content;
		if (!is_strgreater(km_curr->key, km->key))
		{
			swap_keymap(lst, km, prev, curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	ft_lstadd_back(lst, ft_lstnew(km));
}

t_list	*sort_keymap_alpha(t_list *lst)
{
	t_list	*new;
	t_list	*curr;
	t_km	*km_curr;

	if (!lst)
		return (0);
	new = ft_lstnew(lst->content);
	curr = lst->next;
	while (curr)
	{
		km_curr = (t_km *)curr->content;
		insert_keymap_alpha(&new, km_curr);
		curr = curr->next;
	}
	return (new);
}
