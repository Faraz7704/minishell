/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:06:26 by szhakypo          #+#    #+#             */
/*   Updated: 2022/08/17 18:09:18 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_key	*lstlast(t_key *lst)
{
	t_key	*next_lst;

	if (!lst)
		return (0);
	next_lst = lst;
	while (next_lst->next)
		next_lst = next_lst->next;
	return (next_lst);
}

void	ftt_lstadd_back(t_key **lst, t_key *new)
{
	t_key	*last_lst;

	if (!lst[0])
		lst[0] = new;
	else
	{
		last_lst = lstlast(lst[0]);
		last_lst->next = new;
	}
}

int	ft_strclen(char *s, char c)
{
	int	i;
	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

int	keydup(char **dst, char *src, int size)
{
	int	new;
	
	dst[0] = malloc(sizeof(char *) * size);
	new = ft_strlcpy(dst[0], src, size);
	if (!dst[0])
		return (0);
	return (new);
}

t_key	*init_key(char *keyvalue)
{
	t_key	*new;
	int		size;
	int		index;

	new = malloc(sizeof(t_key));
	size = ft_strclen(keyvalue, '=') + 1;
	index = size;
	keydup(&new->key, keyvalue, size);
	size = ft_strlen(&keyvalue[index]) + 1;
	keydup(&new->val, &keyvalue[index], size);
	return (new);
}

void	list_key_addd(t_key **info, char *env)
{
	t_key	*keymap;
	
	keymap = init_key(env);
	ftt_lstadd_back(info, keymap);
}



