/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:23:00 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/17 13:22:22 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **argv, t_env *env)
{
	int	i;

	i = 1;
	while (argv[i])
		add_keymap(&env->kms, argv[i++]);
	if (i == 1)
		print_export(env->kms);
}
