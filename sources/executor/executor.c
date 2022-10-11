/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:59:38 by fkhan             #+#    #+#             */
/*   Updated: 2022/10/11 20:49:41 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"

char	*full_command_path(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	*dir;
	char	*full;

	i = 0;
	while (env[i] && ncompare(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && len_ch(path, ':') > -1)
	{
		dir = str_ndup(path, len_ch(path, ':'));
		full = make_command(dir, cmd);
		free(dir);
		if (access(full, F_OK) == 0)
			return (full);
		free(full);
		path += len_ch(path, ':') + 1;
	}
	return (cmd);
}

int	exec(char *cmd, char **argv, t_list **kms, char **env)
{
	if (parser_argv(argv) == 1)
		return (1);
	if (ft_strcontains(cmd, "env"))
		print_keymaps(*kms);
	else if (ft_strcontains(cmd, "pwd"))
		ft_pwd();
	else if (ft_strcontains(cmd, "echo"))
		ft_echo(argv);
	else if (ft_strcontains(cmd, "export"))
		ft_export(kms, argv);
	else if (ft_strcontains(cmd, "unset"))
		ft_unset(kms, argv);
	else if (ft_strcontains(cmd, "clear"))
		ft_printf("\e[1;1H\e[2J");
	else if (ft_strcontains(cmd, "exit"))
		ft_exit(kms, argv);
	else
	{
		//DIR *dir;
		//struct dirent *entry;
		//t_list	*temp = find_keymap_key(*kms, "PATH");
		//char	**path = ft_split(((t_km *)temp->content)->val, ':');
		//int		i = 0;
		char *path = full_command_path(cmd, env);
		execve(path, argv, env);
		//printf("%s\n", comand);
		
		//struct stat info;

		//if ((dir = opendir(cmd)) == NULL)
   		//	perror("opendir() error");
		//else
		//	while ((entry = readdir(dir)) != NULL)
		//	{
		//		if (entry->d_name[0] != '.')
		//		{
		//			strcpy(path, cmd);
       	//			strcat(path, "/");
        //			strcat(path, entry->d_name);
       	//			if (stat(path, &info) != 0)
        // 				 fprintf(stderr, "stat() error on %s: %s\n", path,
        //          	strerror());
       	//			else if (S_ISDIR(info.st_mode))
        //       			traverse(path, indent+1);
		//		}
		//	}
		//printf("%s\n", path[i]);
		//if (execve(path[i], argv, env)  == -1)
		//	i++;
	}
		
	//add_keymap(kms, "OLDPWD");
	
	return (0);
}

int	runcmd(t_cmd *cmd, t_list **kms, char **env)
{
	int			p[2];
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;

	if (cmd == 0)
		return (1);
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (ecmd->argv[0] == 0)
			return (1);
		if (exec(ecmd->argv[0], ecmd->argv, kms, env))
		{
			ft_fprintf(2, "exec %s failed\n", ecmd->argv[0]);
			return (1);
		}
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode) < 0)
		{
			ft_fprintf(2, "open %s failed\n", rcmd->file);
			return (1);
		}
		runcmd(rcmd->cmd, kms, env);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		if (pipe(p) < 0)
		{
			print_error("pipe");
			return (1);
		}
		if (fork1() == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left, kms, env);
		}
		if (fork1() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right, kms, env);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
	}
	else
	{
		print_error("runcmd");
		return (1);
	}
	return (0);
}
