/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:06:26 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/02 19:00:16 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_keymap(t_km *km, char *keyvalue)
{
	int		size;
	int		index;

	size = ft_strclen(keyvalue, '=') + 1;
	index = size;
	km->key = ft_strldup(keyvalue, size);
	size = ft_strlen(&keyvalue[index]) + 1;
	km->val = ft_strldup(&keyvalue[index], size);
}

void	add_keymap(t_km **kms, char *keyvalue)
{
	t_km	*keymap;

	keymap = malloc(sizeof(t_km));
	update_keymap(keymap, keyvalue);
	km_lstadd_back(kms, keymap);
}

t_km	*init_keymaps(char **env)
{
	int		i;
	int		size;
	t_km	*kms;

	i = 0;
	kms = NULL;
	size = ft_strdlen(env);
	while (i < size)
		add_keymap(&kms, env[i++]);
	return (kms);
}
