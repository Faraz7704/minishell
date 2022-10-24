/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:23:00 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/25 02:37:58 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verify_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
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
		if (ft_isdigit(*argv[i]) || !verify_key(argv[i]))
			ft_fprintf(2, "export: `%s': not a valid identifier\n", argv[i]);
		else
			add_keymap(&env->kms, argv[i]);
		i++;
	}
	if (i == 1)
		print_export(env->kms);
}
