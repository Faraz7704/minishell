/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:39:54 by szhakypo          #+#    #+#             */
/*   Updated: 2022/11/11 21:32:42 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isspace_atoi(int c)
{
	if (ft_strchr(WHITESPACE, c))
		return (1);
	else
		return (0);
}

static int	check_numeric(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 20)
		return (1);
	if (str[i] != '-' && !ft_isdigit(str[i]))
		return (1);
	i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

unsigned long long	ft_atoull(char *str, int *minus)
{
	int					i;
	unsigned long long	num;

	i = 0;
	num = 0;
	while (ft_isspace_atoi(str[i]))
		i = i + 1;
	if (str[i] == '-')
		*minus = 1;
	if (str[i] == '-' || str[i] == '+')
		i = i + 1;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + str[i] - '0';
		i = i + 1;
	}
	return (num);
}

void	ft_exit(char **argv, t_env *env)
{
	int		minus;

	(void) env;
	minus = 0;
	if (!argv || !argv[1])
		exit_app(0, 0, 0);
	if (argv[2])
	{
		ft_fprintf(2, "exit: too many arguments");
		return ;
	}
	ft_atoull(argv[1], &minus);
	if (check_numeric(argv[1]) || \
		((!minus && ft_atoull(argv[1], &minus) > __LONG_LONG_MAX__) || \
		(minus && ft_atoull(argv[1], &minus) - 1 > __LONG_LONG_MAX__)))
	{
		ft_fprintf(2, "exit: %s: numeric argument required\n", argv[1]);
		exit_app(255, 0, 0);
	}
	ft_printf("exit\n");
	g_var = ft_atoi(argv[1]) % 256;
	exit_app(g_var, 0, 0);
}
