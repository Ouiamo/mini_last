/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:18:25 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/12 18:18:36 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_minishell *minishell, int i, t_outils *exec)
{
	if (builtins(minishell, i, exec) == -1)
	{
		g_exit_status = 0;
		exec->path = search_paths("PATH", minishell);
		exec->paths = ft_split(exec->path, ':');
		if (minishell->shell[i].cmd[0] == '\0')
			msg_error(2, minishell->shell[i].cmd, exec);
		if (!ft_strcmp(minishell->shell[i].split_cmd[0], "..") && exec->path)
			msg_error(2, minishell->shell[i].cmd, exec);
		check_special_case(minishell->shell[i].split_cmd, exec);
		check_cmd(minishell, i, exec);
		execve(exec->cmd_path, minishell->shell[i].split_cmd, exec->envp);
		ft_error("execve");
	}
	return (g_exit_status);
}

void	check_status(int *status)
{
	if (WIFEXITED(*status))
		g_exit_status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == SIGQUIT)
		{
			printf("Quit (core dumped)\n");
			g_exit_status = 131;
		}
		else if (WTERMSIG(*status) == SIGINT)
		{
			printf("\n");
			g_exit_status = 130;
		}
	}
}

int	exec_one_cmd(t_outils *exec, t_minishell *minishell)
{
	int	status;

	if (builtins(minishell, 0, exec) == -1)
	{
		exec->id = fork();
		signal(SIGINT, SIG_IGN);
		if (exec->id < 0)
			return (error_p("fork"));
		else if (exec->id == 0)
		{
			handling_signals(POS2, minishell);
			g_exit_status = execute(minishell, 0, exec);
		}
		waitpid(exec->id, &status, 0);
		check_status(&status);
	}
	return (g_exit_status);
}

int	one_cmd(t_minishell *minishell, t_outils *exec)
{
	if ((minishell->shell[0].infiles && minishell->shell[0].infiles->fd > -1)
		|| (minishell->shell[0].outfiles && minishell
			->shell[0].outfiles->fd > -1))
		dup_file(minishell, 0, exec);
	if (!minishell->shell[0].cmd)
	{
		restore_in_out(exec);
		return (g_exit_status = 0);
	}
	exec_one_cmd(exec, minishell);
	restore_in_out(exec);
	return (g_exit_status);
}

int	execution(t_minishell *minishell, t_outils *exec)
{
	int	status;

	if (minishell->nbr_commands == -1)
		return (0);
	exec->in = -2;
	exec->out = -2;
	status = 0;
	save_last_cmd(minishell);
	if (minishell->shell[0].ambiguous == 1 && minishell->nbr_commands == 1)
		return (close_all(minishell), g_exit_status = 1);
	if (minishell->nbr_commands == 1)
		return (one_cmd(minishell, exec));
	if (ft_pipe(minishell, exec) < 0)
		return (g_exit_status = 1);
	if (ft_fork(exec, minishell, &status) < 0)
		return (g_exit_status = 1);
	ft_close(exec);
	close_all(minishell);
	ft_wait(exec, minishell->nbr_commands, &status, minishell);
	return (g_exit_status);
}
