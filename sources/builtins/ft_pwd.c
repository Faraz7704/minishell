/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:45:11 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/17 23:33:58 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pwd(void)
{
	char	*buff;

	buff = NULL;
	return (getcwd(buff, 0));
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = ft_get_pwd();
	if (pwd)
		printf("%s\n", pwd);
	else
		printf("Error\n");
	free(pwd);
}

char	*ft_add_pwd(char *key, t_env *env)
{
	t_list	*curr;
	char	*keyvalue;
	char	*keytemp;

	keyvalue = NULL;
	curr = find_keymap_key(env->kms, key);
	if (curr)
	{
		keytemp = ft_strjoin(key, "=");
		keyvalue = ft_strjoin(keytemp, ft_get_pwd());
		free(keytemp);
		update_keymap((t_km *)curr->content, keyvalue);
	}
	return (keyvalue);
}
