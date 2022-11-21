/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:59:13 by szhakypo          #+#    #+#             */
/*   Updated: 2022/11/21 15:11:01 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//static void	sig_handler(int sig_num)
//{
//	if (sig_num == SIGINT)
//	{
//		ft_printf("\n");
//		rl_on_new_line();
//		rl_replace_line("", 0);
//		rl_redisplay();
//	}
//	return ;
//}

//static void new_line_prom(int signum)
//{
//	(void)signum;
//	g_appinfo.exit_status = 130;
//	write(1, "\n", 1);
//}

static void	quit_func(int signum)
{
	(void)signum;
	g_appinfo.exit_status = 131;
	ft_printf("Quit\n");
}

void	define_input_signals(void)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	define_exec_signals(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, quit_func);
}

void	ctrl_d(void)
{
	g_appinfo.exit_status = 131;
	ft_printf("Exit");
	exit_app(g_appinfo.exit_status);
}

void	ctrl_c(int sig)
{
	int		ret;

	(void)sig;
	g_appinfo.exit_status = 130;
	ret = waitpid(-1, NULL, WNOHANG);
	if (ret == -1 && sig == SIGINT)
	{
		g_appinfo.exit_status = 1;
		update_exitstatus();
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handler_heredoc(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(1, "\n", 1);
		exit_app(1);
	}
}
