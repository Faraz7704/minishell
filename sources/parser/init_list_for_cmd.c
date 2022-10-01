/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_for_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:20:07 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/01 16:21:34 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd_list(char *str)
{
	t_cmd	*cmd;
	char	**s;
	int		i;
	printf("DAIUDHIAU\n");
	cmd = malloc(sizeof(t_cmd));
	s = ft_split(str, ' ');
	i = 0;
	while(s[i] != NULL)
		ft_list_cmd_add(s[i++], &cmd);
	free(s);
	printf("%s\n", cmd->str);
}

void	ft_list_cmd_add(char *str, t_cmd **cmd)
{
	t_cmd	*new;
	
	new = malloc(sizeof(t_cmd));
	new->str = ft_strdup(str);
	printf("%s\n", new->str);
	ft_cmd_add(cmd, new);
}

void	ft_cmd_add(t_cmd **lst, t_cmd *new)
{
	t_cmd	*lst_cmd;

	if(!lst[0])
		lst[0] = new;
	else
	{
		lst_cmd = cmd_lstlast(lst[0]);
		lst_cmd->next = new;
	}
}

t_cmd	*cmd_lstlast(t_cmd *cmd)
{
	t_cmd	*next_lst;
	
	if (!cmd)
		return (0);
	next_lst = cmd;
	while (next_lst->next)
		next_lst = next_lst->next;
	return(next_lst);
}