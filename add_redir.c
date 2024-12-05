/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:33:36 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/12 15:41:38 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	ambiguous(t_shell shell, char *name, t_minishell *minishell)
{
	(void)minishell;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	shell.ambiguous = 1;
	g_exit_status = 1;
	return (shell);
}

t_shell	add_in_file(char *redir, t_shell shell, char *name,
		t_minishell *minishell)
{
	t_list	*new_file;
	t_list	*list_file;

	new_file = ft_malloc(sizeof(t_list), 0);
	list_file = shell.infiles;
	if (redir[1])
	{
		new_file->fd = my_heredoc(name, minishell);
		new_file->content = ft_strdup("/tmp/heredoc");
	}
	else
	{
		new_file->content = remove_quotes((herdoc_expand(name, minishell, 1)));
		if ((!*(new_file->content) && *remove_quotes(name))
			|| (spaces(remove_quotes((herdoc_expand(name, minishell, 1))))
				&& !spaces(name) && !quote_type(name)))
			return (shell = ambiguous(shell, name, minishell));
		else
			new_file->fd = ft_help(new_file->content, &shell, minishell);
	}
	new_file->next = list_file;
	shell.infiles = new_file;
	return (shell);
}

t_shell	add_out_file(char *redir, t_shell shell, char *name,
		t_minishell *minishell)
{
	t_list	*new_file;
	t_list	*list_file;

	new_file = ft_malloc(sizeof(t_list), 0);
	list_file = shell.outfiles;
	new_file->content = remove_quotes((herdoc_expand(name, minishell, 1)));
	if ((!*(new_file->content) && *remove_quotes(name))
		|| (spaces(remove_quotes((herdoc_expand(name, minishell, 1))))
			&& !spaces(name) && !quote_type(name)))
		shell = ambiguous(shell, name, minishell);
	else
	{
		if (redir[1])
			new_file->fd = open(new_file->content,
					O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			new_file->fd = open(new_file->content, O_CREAT | O_WRONLY | O_TRUNC,
					0644);
		if (access(new_file->content, F_OK) < 0 || access(new_file->content,
				W_OK) < 0 || new_file->fd < 0)
			ft_error1(new_file->content, &shell, minishell);
		new_file->next = list_file;
		shell.outfiles = new_file;
	}
	return (shell);
}

t_shell	add_redir(char ***arr, t_shell shell, t_minishell *minishell)
{
	char	*my_redir;

	my_redir = **arr;
	(*arr)++;
	if (my_redir[0] == '>')
		shell = add_out_file(my_redir, shell, **arr, minishell);
	if (my_redir[0] == '<')
		shell = add_in_file(my_redir, shell, **arr, minishell);
	if (shell.ambiguous == 1)
	{
		while (**arr && ***arr != '|')
		{
			if (minishell->nbr_commands == -1)
				break ;
			my_redir = **arr;
			if (my_redir[0] == '<' && my_redir[1] == '<')
			{
				(*arr)++;
				shell = add_in_file(my_redir, shell, **arr, minishell);
			}
			(*arr)++;
		}
		(*arr)--;
	}
	return (shell);
}
