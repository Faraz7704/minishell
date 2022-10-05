/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:39:54 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/05 19:27:14 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	ft_atoi_for_exit(char *c)
//{
//	int	i;
//	int neg;

	
//}


void	ft_exit(t_list **kms, char **argv)
{
	free(kms);
	exit(ft_atoi(argv[1]));
}