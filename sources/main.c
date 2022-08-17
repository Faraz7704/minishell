/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:44:41 by fkhan             #+#    #+#             */
/*   Updated: 2022/08/17 20:32:16 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//t_sig	g_sig;//glabal signal;
// static void	parsing(char **av, char **env)
// {
// 	(void)av;
// 	(void)env;
// 	ft_printf("Hello World!");
// }

int	main(int ac, char **av, char **env)
{
	t_info	*info;
	t_key	*keys;
	int		i;


	(void)ac;
	(void)av;
	info = malloc(sizeof(t_info));
	i = 0;
	while (i < size_liness(env))
		list_key_addd(&keys, env[i++]);
	while (1)
	{
		info->cmd = readline(BEGIN(49, 34)"minishell>$"CLOSE);
		find_cmd(info);
	}
	free(info->cmd);
	return (0);
}
