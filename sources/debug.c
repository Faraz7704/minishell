/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:40:37 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/03 02:22:31 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *s)
{
	ft_fprintf(2, "%s\n", s);
	exit(1);
}

void	print_keymaps(t_km *kms)
{
	t_km	*curr;

	curr = kms;
	while (curr)
	{
		if (curr->val != NULL)
			ft_printf("%s=%s\n", curr->key, curr->val);
		curr = curr->next;
	}
}


void	print_export(t_km *kms, char **av)
{
	int	i;
	t_km	*tmp;

	tmp = kms;
	i = 1;
	if (av[1] != NULL)
		while(av[i] != NULL)
		{
			add_keymap(&kms, av[i]);
			i++;
		}
	else
	{
		while(tmp)
		{
			printf("declare -x %s=%s\n", tmp->key, tmp->val);
			tmp= tmp->next;
		}
	}
}