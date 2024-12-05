/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:20:51 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/11 01:02:22 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_p(char *str)
{
	write(2, "minishell: ", 11);
	perror(str);
	return (-1);
}

void	ft_close(t_outils *t)
{
	int	i;

	i = 0;
	while (i < t->nbr_pipes)
	{
		close(t->fd[i][0]);
		close(t->fd[i][1]);
		i++;
	}
}

int	ft_pipe(t_minishell *minishell, t_outils *t)
{
	int	i;

	t->nbr_pipes = minishell->nbr_commands - 1;
	t->fd = ft_malloc2(t->nbr_pipes * sizeof(int *), 0);
	i = 0;
	if (!(t->fd))
		return (-1);
	while (i < t->nbr_pipes)
	{
		t->fd[i] = ft_malloc2(2 * sizeof(int), 0);
		if (!(t->fd[i]))
			return (-1);
		if (pipe(t->fd[i]) == -1)
			return (error_p("pipe"));
		i++;
	}
	return (0);
}

void	dup_outfile(t_minishell *minishell, int i)
{
	t_list	*head_out;

	head_out = minishell->shell[i].outfiles;
	if (head_out && head_out->fd > -1)
	{
		if (!ft_strcmp(head_out->content, "/dev/stdout") && head_out->next)
		{
			if (dup2(head_out->next->fd, STDOUT_FILENO) < 0)
				ft_error("dup");
		}
		else
		{
			if (dup2(head_out->fd, STDOUT_FILENO) < 0)
				ft_error("dup");
		}
	}
}

void	dup_file(t_minishell *minishell, int i, t_outils *t)
{
	t_list	*head_inf;
	t_list	*head_out;

	head_inf = minishell->shell[i].infiles;
	head_out = minishell->shell[i].outfiles;
	if (head_inf && head_inf->fd >= 0)
	{
		save_in_out(t, 0);
		if (!ft_strcmp(head_inf->content, "/dev/stdin") && head_inf->next)
			dup2(head_inf->next->fd, STDIN_FILENO);
		else
			dup2(head_inf->fd, STDIN_FILENO);
		close_fd(head_inf);
	}
	if (head_out && head_out->fd >= 0)
	{
		save_in_out(t, 1);
		if (!ft_strcmp(head_out->content, "/dev/stdout") && head_out->next)
			dup2(head_out->next->fd, STDOUT_FILENO);
		else
			dup2(head_out->fd, STDOUT_FILENO);
		close_fd(head_out);
	}
}
