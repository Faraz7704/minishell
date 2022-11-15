/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:45:11 by szhakypo          #+#    #+#             */
/*   Updated: 2022/11/15 18:49:15 by szhakypo         ###   ########.fr       */
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
		ft_printf("%s\n", pwd);
	else
		print_error("Error\n");
	free(pwd);
}

void	ft_update_pwd(char *key, t_env *env)
{
	t_list	*curr;
	char	*keyvalue;
	char	*keytemp;
	char	*pwdtemp;

	keyvalue = NULL;
	curr = find_keymap_key(env->kms, key);
	if (curr)
	{
		keytemp = ft_strjoin(key, "=");
		pwdtemp = ft_get_pwd();
		if (!pwdtemp)
			return ;
		keyvalue = ft_strjoin(keytemp, pwdtemp);
		free(keytemp);
		free(pwdtemp);
		free(((t_km *)curr->content)->key);
		free(((t_km *)curr->content)->val);
		update_keymap((t_km *)curr->content, keyvalue);
		free(keyvalue);
	}
}
