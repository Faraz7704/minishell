/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:44:46 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/11 20:45:14 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"

int	len_ch(char *str, char ch)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ch)
		i++;
	if (str[i] == ch)
		return (i);
	return (-1);
}

// Если строки до n одинаковы, возвращаем 0

int	ncompare(char *str1, char *str2, int n)
{
	while (*str1 && *str2 && *str1 == *str2 && --n > 0)
	{
		str1++;
		str2++;
	}
	return (*str2 - *str1);
}

// соединяем путь и команду

char	*make_command(char *path, char *bin)
{
	int		i;
	int		j;
	char	*buff;

	buff = malloc(sizeof(char) * (len_ch(path, 0) + len_ch(bin, 0) + 2));
	i = 0;
	j = 0;
	while (path[j])
		buff[i++] = path[j++];
	buff[i++] = '/';
	j = 0;
	while (bin[j])
		buff[i++] = bin[j++];
	buff[i] = 0;
	return (buff);
}

// Копируем строку до n

char	*str_ndup(char *str, unsigned int n)
{
	unsigned int	i;
	char			*buff;

	i = 0;
	buff = malloc(sizeof(char) * (n + 1));
	while (i < n)
		buff[i++] = *str++;
	buff[n] = 0;
	return (buff);
}