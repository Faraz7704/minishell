/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:28:25 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/17 13:23:01 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **argv, t_env *env)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		remove_keymap(&env->kms, argv[i]);
		i++;
	}
}
