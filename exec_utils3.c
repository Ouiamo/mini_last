/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:21:26 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/12 18:20:42 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msg_error(int n, char *str, t_outils *exec)
{
	if (n == 1)
	{
		write(2, "minishell: ", 12);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (n == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (n == 3)
	{
		write(2, "minishell: ", 12);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		restore_in_out(exec);
		ft_malloc2(-2, 0);
		ft_malloc(-2, 0);
		exit(126);
	}
	restore_in_out(exec);
	ft_malloc2(-2, 0);
	ft_malloc(-2, 0);
	exit(127);
}

void	null_path(t_minishell *minishell, int *i, t_outils *exec)
{
	if (!access(minishell->shell[*i].split_cmd[0], F_OK))
	{
		if (!access(minishell->shell[*i].cmd, X_OK))
			exec->cmd_path = minishell->shell[*i].cmd;
		else if (access(minishell->shell[*i].cmd, X_OK) != 0)
			msg_error(3, minishell->shell[*i].cmd, exec);
	}
	else
		msg_error(1, minishell->shell[*i].cmd, exec);
}

void	check_cmd(t_minishell *minishell, int i, t_outils *exec)
{
	if ((!ft_strncmp(minishell->shell[i].split_cmd[0], "/", 1)
			|| !ft_strncmp(minishell->shell[i].split_cmd[0], "./", 2)
			|| !ft_strncmp(minishell->shell[i].split_cmd[0], "../", 3))
		&& !access(minishell->shell[i].cmd, X_OK))
		exec->cmd_path = minishell->shell[i].cmd;
	else if ((!ft_strncmp(minishell->shell[i].split_cmd[0], "/", 1)
			|| !ft_strncmp(minishell->shell[i].split_cmd[0], "./", 2)
			|| !ft_strncmp(minishell->shell[i].split_cmd[0], "../", 3))
		&& access(minishell->shell[i].cmd, X_OK) != 0)
	{
		if (access(minishell->shell[i].split_cmd[0], F_OK) == 0)
			msg_error(3, minishell->shell[i].cmd, exec);
		else
			msg_error(1, minishell->shell[i].cmd, exec);
	}
	else if (exec->path == NULL)
		null_path(minishell, &i, exec);
	else
		exec->cmd_path = ckeck_path_cmd(minishell->shell[i].split_cmd[0],
				exec->paths);
	if (exec->cmd_path == NULL)
		msg_error(2, minishell->shell[i].split_cmd[0], exec);
}

void	restore_in_out(t_outils *t)
{
	if (t->in != -2)
	{
		if (dup2(t->in, STDIN_FILENO) < 0)
			ft_error("dup");
		close(t->in);
	}
	if (t->out != -2)
	{
		if (dup2(t->out, STDOUT_FILENO) < 0)
			ft_error("dup");
		close(t->out);
	}
}
