/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:06:26 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/17 13:35:18 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_keymap(void *content)
{
	t_km	*km;

	km = (t_km *)content;
	free(km->key);
	if (km->val && *km->val)
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
