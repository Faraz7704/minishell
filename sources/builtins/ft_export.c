/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:23:00 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/23 18:50:56 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **argv, t_env *env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_isalpha(*argv[i]))
			add_keymap(&env->kms, argv[i]);
		else
			ft_fprintf(2, "export: `%s': not a valid identifier\n", argv[i]);
		i++;
	}
	if (i == 1)
		print_export(env->kms);
}
