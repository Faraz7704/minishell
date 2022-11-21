/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:06:26 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/25 02:19:20 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **env)
{
	size_t	i;
	size_t	size;
	t_env	*new;
	t_km	*km;

	new = malloc(sizeof(t_env));
	if (!new)
		print_error("malloc error\n");
	size = ft_strdlen(env);
	new->kms = NULL;
	new->env = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new->env)
		print_error("malloc error\n");
	i = 0;
	while (i < size)
	{
		km = malloc(sizeof(t_km));
		if (!km)
			print_error("malloc error\n");
		update_keymap(km, env[i]);
		new->env[i] = ft_strdup(env[i]);
		ft_lstadd_back(&new->kms, ft_lstnew(km));
		i++;
	}
	new->env[i] = ft_strdup("?=0");
	add_keymap(&new->kms, new->env[i], 0);
	new->env[++i] = 0;
	add_keymap(&new->kms, "OLDPWD", 1);
	return (new);
}

char	**ft_getenv(t_list *lst)
{
	t_list	*curr;
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!ret)
		print_error("malloc error\n");
	curr = lst;
	i = 0;
	while (curr)
	{
		ret[i++] = merge_keymap((t_km *)curr->content);
		curr = curr->next;
	}
	ret[i] = 0;
	return (ret);
}

void	update_env(t_env *env)
{
	ft_clearsplit(env->env);
	env->env = ft_getenv(env->kms);
}

void	clear_keymap(void *content)
{
	t_km	*km;

	km = (t_km *)content;
	free(km->key);
	if (km->val)
		free(km->val);
	free(km);
}

void	clear_env(t_env *env)
{
	if (!env)
		return ;
	ft_clearsplit(env->env);
	ft_lstclear(&env->kms, clear_keymap);
	free(env->kms);
	free(env);
}
