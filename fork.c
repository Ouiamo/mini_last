/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:01:16 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/11 00:45:05 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_multi_cmd(t_outils *t, int i, t_minishell *minishell)
{
	if (i == 0)
	{
		if (dup2(t->fd[0][1], STDOUT_FILENO) < 0)
			ft_error("dup");
	}
	else if (i == t->nbr_pipes)
	{
		if (dup2(t->fd[i - 1][0], STDIN_FILENO) < 0)
			ft_error("dup");
	}
	else
	{
		if (dup2(t->fd[i - 1][0], STDIN_FILENO) < 0)
			ft_error("dup");
		if (dup2(t->fd[i][1], STDOUT_FILENO) < 0)
			ft_error("dup");
	}
	ft_close(t);
	close_all(minishell);
}

void	dup_multi_cmd_infile(t_outils *t, int i, t_minishell *minishell)
{
	if (i == 0)
	{
		dup_infile(minishell, i);
		if (dup2(t->fd[0][1], STDOUT_FILENO) < 0)
			ft_error("dup");
	}
	else if (i == t->nbr_pipes)
		dup_infile(minishell, i);
	else
	{
		dup_infile(minishell, i);
		if (dup2(t->fd[i][1], STDOUT_FILENO) < 0)
			ft_error("dup");
	}
	ft_close(t);
	close_all(minishell);
}

void	dup_multi_cmd_outfile(t_outils *t, int i, t_minishell *minishell)
{
	if (i == 0)
	{
		if (minishell->shell[i].infiles && minishell->shell[i].infiles->fd)
			dup_infile(minishell, i);
		dup_outfile(minishell, i);
	}
	else
	{
		if (minishell->shell[i].infiles && minishell->shell[i].infiles->fd)
			dup_infile(minishell, i);
		else
		{
			if (dup2(t->fd[i - 1][0], STDIN_FILENO) < 0)
				ft_error("dup");
		}
		dup_outfile(minishell, i);
	}
	ft_close(t);
	close_all(minishell);
}

void	child(t_outils *t, t_minishell *minishell, int *status, int i)
{
	if ((minishell->shell[i].outfiles && minishell->shell[i].outfiles->fd >= 0))
		dup_multi_cmd_outfile(t, i, minishell);
	else if (minishell->shell[i].infiles
		&& minishell->shell[i].infiles->fd >= 0)
		dup_multi_cmd_infile(t, i, minishell);
	else
		dup_multi_cmd(t, i, minishell);
	if (minishell->shell[i].cmd)
		g_exit_status = execute(minishell, i, t);
	else
		g_exit_status = *status;
	free_malloc();
	exit(g_exit_status);
}

int	ft_fork(t_outils *t, t_minishell *minishell, int *status)
{
	int	i;

	i = 0;
	t->pid = ft_malloc2(minishell->nbr_commands * sizeof(int), 0);
	if (!t->pid)
		return (-1);
	while (i < minishell->nbr_commands)
	{
		if (minishell->shell[i].ambiguous == 1)
		{
			i++;
			g_exit_status = 1;
			continue ;
		}
		t->pid[i] = fork();
		handling_signals(POS2, minishell);
		if (t->pid[i] < 0)
			return (error_p("fork"));
		else if (t->pid[i] == 0)
			child(t, minishell, status, i);
		i++;
	}
	return (g_exit_status);
}
