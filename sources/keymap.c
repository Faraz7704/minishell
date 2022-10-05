/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:06:26 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/05 19:10:56 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (curr && !ft_strequals(((t_km *)curr->content)->key, key))
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
		update_keymap((t_km *)curr->content, keyvalue);
	else
	{
		km = malloc(sizeof(t_km));
		update_keymap(km, keyvalue);
		ft_lstadd_back(lst, ft_lstnew(km));
	}
}

t_list	*init_keymaps(char **env)
{
	size_t	i;
	size_t	size;
	t_list	*new;
	t_km	*km;

	i = 0;
	new = NULL;
	size = ft_strdlen(env);
	while (i < size)
	{
		km = malloc(sizeof(t_km));
		update_keymap(km, env[i]);
		ft_lstadd_back(&new, ft_lstnew(km));
		i++;
	}
	return (new);
}

void	remove_keymap(t_list **lst, char *key)
{
	t_list	*curr;
	t_list	*last;
	t_list	*next;

	curr = *lst;
	last = NULL;
	while (curr)
	{
		next = curr->next;
		if (ft_strequals(((t_km *)curr->content)->key, key))
		{
			if (last)
				last->next = next;
			else
				*lst = next;
			free(curr);
			curr = NULL;
		}
		last = curr;
		curr = next;
	}
}
