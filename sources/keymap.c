/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:06:26 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/04 13:24:44 by szhakypo         ###   ########.fr       */
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

t_km	*find_keymap_key(t_km *kms, char *keyvalue)
{
	t_km	*curr;
	size_t	size;
	char	*key;

	size = ft_strclen(keyvalue, '=') + 1;
	key = ft_strldup(keyvalue, size);
	curr = kms;
	while (curr && !ft_strequals(curr->key, key))
		curr = curr->next;
	free(key);
	return (curr);
}

void	add_keymap(t_km **kms, char *keyvalue)
{
	t_km	*keymap;

	keymap = find_keymap_key(kms[0], keyvalue);
	if (keymap)
		update_keymap(keymap, keyvalue);
	else
	{
		keymap = malloc(sizeof(t_km));
		update_keymap(keymap, keyvalue);
		keymap->next = NULL;
		km_lstadd_back(kms, keymap);
	}
}

t_km	*init_keymaps(char **env)
{
	size_t	i;
	size_t	size;
	t_km	*kms;

	i = 0;
	kms = NULL;
	size = ft_strdlen(env);
	while (i < size)
		add_keymap(&kms, env[i++]);
	return (kms);
}

void	ft_list_remove_if(t_km **begin_list, char *data_ref, int (*cmp)())
{
	t_km	*current;
	t_km	*last;
	t_km	*next;

	current = *begin_list;
	last = ((void *)0);
	while (current)
	{
		next = current->next;
		if (cmp(current->key, data_ref) == 0)
		{
			if (last)
				last->next = current->next;
			else
				*begin_list = current->next;
			free(current);
			current = ((void *)0);
		}
		last = current;
		current = next;
	}	
}