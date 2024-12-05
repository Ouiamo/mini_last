/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:33:55 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/12 19:50:28 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rest(char **line, char *limiter)
{
	if (!*line)
	{
		ft_putstr_fd("minishell: warning: "
			"here-document delimited by end-of-file (wanted `", 2);
		(ft_putstr_fd(remove_quotes(limiter), 2), ft_putstr_fd("\')\n", 2));
	}
	if (*line)
		free(*line);
}

char	*get_user_text(char *limiter)
{
	static char	*line;
	char		*text;
	int			i;

	i = 0;
	text = NULL;
	signal(SIGINT, sig_here_doc);
	line = readline(">");
	while (line && ft_strcmp(line, remove_quotes(limiter)))
	{
		if (i++ == 0)
		{
			text = ft_other_join(line, "\n");
			free(line);
		}
		else
		{
			text = ft_other_join(text, line);
			text = ft_other_join(text, "\n");
			free(line);
		}
		line = readline(">");
	}
	rest(&line, limiter);
	return (text);
}

void	chiled_her(char *limiter, int *fd, t_minishell *minishell, char *text)
{
	int	save;

	save = g_exit_status;
	g_exit_status = *fd;
	text = get_user_text(limiter);
	g_exit_status = save;
	if (text && !no_quotes(limiter))
		text = herdoc_expand(text, minishell, 0);
	if (text)
		write(*fd, text, ft_strlen(text));
	close(*fd);
	free_malloc();
	exit(g_exit_status == 0);
}

int	my_heredoc_util(char *limiter, int *fd, t_minishell *minishell)
{
	char	*text;
	pid_t	pid;
	int		status;

	if (minishell->save_fd != -2)
	{
		close (minishell->save_fd);
		minishell->save_fd = -2;
	}
	pid = fork();
	text = NULL;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid < 0)
		return (her_util(fd));
	else if (pid == 0)
		chiled_her(limiter, fd, minishell, text);
	waitpid(pid, &status, 0);
	close(*fd);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	return (g_exit_status);
}

int	my_heredoc(char *limiter, t_minishell *minishell)
{
	int	fd;

	fd = 0;
	fd = open("/tmp/heredoc", O_CREAT | O_WRONLY | O_TRUNC | O_EXCL, 0600);
	if (fd < 0)
	{
		printf("you traying to cheat me NIIHAHAHAHA (T-T)\\(^-^)\n");
		return (-1);
	}
	if (my_heredoc_util(limiter, &fd, minishell) == 130)
	{
		minishell->nbr_commands = -1;
		unlink("/tmp/heredoc");
		return (-1);
	}
	fd = open("/tmp/heredoc", O_RDONLY);
	minishell->save_fd = fd;
	unlink("/tmp/heredoc");
	return (fd);
}
