/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:37:13 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/12 18:20:02 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str)
{
	write(2, "minishell: ", 11);
	perror(str);
	ft_malloc2(-2, 0);
	ft_malloc(-2, 0);
	exit(g_exit_status = 1);
}

void	close_fd(t_list *file)
{
	if (!file)
		return ;
	while (file)
	{
		if (file->fd > -1)
			close(file->fd);
		file = file->next;
	}
}

void	save_in_out(t_outils *t, int n)
{
	if (n == 0)
		t->in = dup(STDIN_FILENO);
	if (n == 1)
		t->out = dup(STDOUT_FILENO);
}

void	ft_wait(t_outils *t, int n_cmd, int *status, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < n_cmd)
	{
		if (minishell->shell[i].ambiguous == 1)
		{
			g_exit_status = 1;
			i++;
		}
		else
		{
			waitpid(t->pid[i], status, 0);
			if (WIFEXITED(*status))
				g_exit_status = WEXITSTATUS(*status);
			i++;
		}
	}
}

void	dup_infile(t_minishell *minishell, int i)
{
	t_list	*head_inf;

	head_inf = minishell->shell[i].infiles;
	if (head_inf && head_inf->fd > -1)
	{
		if (!ft_strcmp(head_inf->content, "/dev/stdin") && head_inf->next)
		{
			if (dup2(head_inf->next->fd, STDIN_FILENO) < 0)
				ft_error("dup");
		}
		else
		{
			if (dup2(head_inf->fd, STDIN_FILENO) < 0)
				ft_error("dup");
		}
	}
}
