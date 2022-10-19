/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:01:33 by szhakypo          #+#    #+#             */
/*   Updated: 2022/10/20 01:04:34 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	ft_chdir(char *path, t_list	*kms)
{
	t_list	*home_km;
	char	*parse_path;

	if (!path || *path == '~')
	{
		home_km = find_keymap_key(kms, "HOME");
		if (home_km && chdir(((t_km *)home_km->content)->val) < 0)
			ft_fprintf(2, "cd: %s: No such file or directory\n", path);
		return ;
	}
	parse_path = ft_first_word(path);
	if (chdir(parse_path) < 0)
		ft_fprintf(2, "cd: %s: No such file or directory\n", parse_path);
	free(parse_path);
}

void	ft_cd(char **argv, t_env *env)
{
	ft_update_pwd("OLDPWD", env);
	ft_chdir(argv[1], env->kms);
	ft_update_pwd("PWD", env);
}
