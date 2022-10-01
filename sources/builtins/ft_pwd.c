/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:45:11 by szhakypo          #+#    #+#             */
/*   Updated: 2022/09/30 17:01:22 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_pwd()
{
	char *buff;

	buff = NULL;
	return (getcwd(buff, 0));
}

void	ft_pwd()
{
	char	*pwd;

	pwd = ft_get_pwd();
	if(pwd)
		printf("%s\n", pwd);
	else
		printf("Error\n");
	free(pwd);
}

