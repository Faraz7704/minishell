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

static int	strdigitlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]))
		i++;
	return (i);
}

static int	check(const char *str, char *range)
{
	int		i;
	int		flag;
	int		len;

	len = strdigitlen(str);
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	i = 0;
	flag = 0;
	while (i < len)
	{
		if (str[i] < range[i])
			return (0);
		else if (!flag && str[i] > range[i])
			flag = 1;
		i++;
	}
	return (flag);
}

long long	ft_atoull(char *str)
{
	int					i;
	unsigned long long	num;
	int					sign;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_strchr(WHITESPACE, str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (sign > 0 && check(&str[i], "9223372036854775807"))
		return (-1);
	else if (sign < 0 && check(&str[i], "9223372036854775808"))
		return (0);
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * sign);
}

static int	ft_isnumber(long long num, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i == 1 && !ft_isdigit(str[0]))
		return (0);
	if ((num == -1 || num == 0) && i >= 19)
		return (0);
	return (1);
}

void	ft_exit(char **argv, t_env *env)
{
	long long		val;

	(void) env;
	if (!argv || !argv[1])
		exit_app(g_appinfo.exit_status);
	if (argv[2])
	{
		ft_fprintf(2, "exit: too many arguments\n");
		exit_app(1);
	}
	val = ft_atoull(argv[1]);
	if (!ft_isnumber(val, argv[1]))
	{
		ft_fprintf(2, "exit: %s: numeric argument required\n", argv[1]);
		exit_app(255);
	}
	ft_printf("exit\n");
	g_appinfo.exit_status = val % 256;
	exit_app(g_appinfo.exit_status);
}
