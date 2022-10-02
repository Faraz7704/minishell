/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:04:26 by faraz             #+#    #+#             */
/*   Updated: 2022/09/09 23:25:36 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == '\n' || c == '\t' || c == ' ')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

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
	if (len > 10)
		return (1);
	if (len < 10)
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

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (sign > 0 && check(&str[i], "2147483647"))
		return (-1);
	else if (sign < 0 && check(&str[i], "2147483648"))
		return (0);
	while (str[i] != '\0' && ft_isdigit(str[i]))
		result = (result * 10) + (str[i++] - '0');
	return (result * sign);
}
