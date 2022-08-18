/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:44:41 by fkhan             #+#    #+#             */
/*   Updated: 2022/08/18 22:29:07 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"

static void	exit_shell(t_si *si)
{
	free(si->cmd);
	free(si->kms);
	free(si);
}

int	main(int ac, char **av, char **env)
{
	t_si	*si;

	(void)ac;
	(void)av;
	si = malloc(sizeof(t_si));
	si->kms = init_keymaps(env);
	while (1)
	{
		si->cmd = readline(BEGIN(49, 34)"minishell>$"CLOSE);
		parse_cmd(si->cmd);
	}
	exit_shell(si);
	return (0);
}
