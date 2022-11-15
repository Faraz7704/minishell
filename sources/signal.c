/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhakypo <szhakypo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:59:13 by szhakypo          #+#    #+#             */
/*   Updated: 2022/11/11 21:38:00 by szhakypo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	define_input_signals(void)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	ctrl_d(void)
{
	g_appinfo.exit_status = 131;
	ft_printf("Exit");
	exit_app(g_appinfo.exit_status);
}

void	ctrl_c(int sig)
{
	(void)sig;
	g_appinfo.exit_status = 130;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	sig_handler_heredoc(int sig_num)
{
	if (sig_num == SIGINT)
		exit_app(1);
}
