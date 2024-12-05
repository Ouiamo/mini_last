/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:49:28 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/12 17:07:47 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_sig_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

void	sig_here_doc(int signal)
{
	(void)signal;
	close(g_exit_status);
	unlink("/tmp/heredoc");
	write(1, "\n", 1);
	g_exit_status = 130;
	free_malloc();
	exit(g_exit_status);
}

void	hand_child(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_exit_status = 130;
}

void	hand_quit(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
	g_exit_status = 131;
}

void	handling_signals(t_signal_status status, t_minishell *minishell)
{
	(void)minishell;
	if (status == POS1)
	{
		signal(SIGINT, read_sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (status == POS2)
	{
		signal(SIGINT, hand_child);
		signal(SIGQUIT, hand_quit);
	}
}
