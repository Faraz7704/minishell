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
	new->kms = NULL;
	new->env = env;
	i = 0;
	size = ft_strdlen(env);
	while (i < size)
	{
		km = malloc(sizeof(t_km));
		update_keymap(km, env[i]);
		ft_lstadd_back(&new->kms, ft_lstnew(km));
		i++;
	}
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
		ret[i++] = mergekeymap((t_km *)curr->content);
		curr = curr->next;
	}
	ret[i] = 0;
	return (ret);
}

void	update_env(t_env *env)
{
	if (!env->env)
		free(env->env);
	env->env = ft_getenv(env->kms);
}

void	clear_env(t_env *env)
{
	if (!env->env)
		free(env->env);
	ft_lstclear(&env->kms, ft_lstdel);
}
