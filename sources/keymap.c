/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:06:26 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/31 20:20:54 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*merge_keymap(t_km *km)
{
	char	*ret;
	char	*temp;

	ret = ft_strjoin(km->key, "=");
	if (km->val != NULL)
	{
		temp = ret;
		ret = ft_strjoin(temp, km->val);
		free(temp);
	}
	return (ret);
}

void	update_keymap(t_km *km, char *keyvalue)
{
	size_t		size;
	size_t		index;

	size = ft_strclen(keyvalue, '=') + 1;
	index = size;
	km->key = ft_strldup(keyvalue, size);
	if (index >= ft_strlen(keyvalue))
	{
		if (ft_strchr(keyvalue, '='))
			km->val = "";
		else
			km->val = NULL;
		return ;
	}
	size = ft_strlen(&keyvalue[index]) + 1;
	km->val = ft_strldup(&keyvalue[index], size);
}

t_list	*find_keymap_key(t_list *lst, char *keyvalue)
{
	t_list	*curr;
	size_t	size;
	char	*key;

	size = ft_strclen(keyvalue, '=') + 1;
	key = ft_strldup(keyvalue, size);
	curr = lst;
	while (curr && !ft_strequals(key, ((t_km *)curr->content)->key))
		curr = curr->next;
	free(key);
	return (curr);
}

void	add_keymap(t_list **lst, char *keyvalue)
{
	t_list	*curr;
	t_km	*km;

	curr = find_keymap_key(lst[0], keyvalue);
	if (curr)
	{
		km = (t_km *)curr->content;
		free(km->key);
		if (km->val)
			free(km->val);
		update_keymap(km, keyvalue);
	}
	else
	{
		km = malloc(sizeof(t_km));
		if (!km)
			print_error("malloc error\n");
		update_keymap(km, keyvalue);
		ft_lstadd_back(lst, ft_lstnew(km));
	}
}

void	remove_keymap(t_list **lst, char *key)
{
	t_list	*curr;
	t_list	*last;
	t_list	*next;

	curr = lst[0];
	last = NULL;
	while (curr)
	{
		next = curr->next;
		if (ft_strequals(((t_km *)curr->content)->key, key))
		{
			if (last)
				last->next = next;
			else
				lst[0] = next;
			clear_keymap(curr->content);
			free(curr);
			curr = NULL;
		}
		last = curr;
		curr = next;
	}
}
