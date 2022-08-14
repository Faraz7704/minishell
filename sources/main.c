/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 19:44:41 by fkhan             #+#    #+#             */
/*   Updated: 2022/08/14 19:47:07 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	parsing(char **av, char **env)
// {
// 	(void)av;
// 	(void)env;
// 	ft_printf("Hello World!");
// }

int	main(int ac, char **av, char **env)
{
	char	*s;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		s = readline("Faraz GAY $ ");
	}
	return (0);
}
