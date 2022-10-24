/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:23:00 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/25 00:02:18 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int verif_key(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(char **argv, t_env *env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_isdigit(*argv[i]) || !verif_key(argv[i]))
			ft_fprintf(2, "export: `%s': not a valid identifier\n", argv[i]);
		else
			add_keymap(&env->kms, argv[i]);
		i++;
	}
	if (i == 1)
		print_export(env->kms);
}
