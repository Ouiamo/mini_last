/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_others.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaoulad- <oaoulad-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:39:00 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/11 18:54:39 by oaoulad-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	add_pipetype(char *arr, t_shell shell)
{
	if (arr[0] == '|')
		shell.pipe_type = 1;
	return (shell);
}

t_list	*add_flags(char *arr, t_shell shell, t_minishell *minishell)
{
	t_list	*new_flag;
	t_list	*tmp;

	new_flag = ft_malloc(sizeof(t_list), 0);
	if (quote_type(arr) == 34 && quote_type(expand_cmd_line(arr,
				minishell)) != 39)
	{
		if (quote_type(remove_quotes(expand_cmd_line(arr, minishell))) != 39)
			new_flag->content = expand_cmd_line(arr, minishell);
		else
			new_flag->content = remove_quotes(expand_cmd_line(arr, minishell));
	}
	else
		new_flag->content = expand_cmd_line(arr, minishell);
	if (!new_flag->content)
		return (shell.flags);
	new_flag->next = NULL;
	if (!shell.flags)
		return (new_flag);
	tmp = shell.flags;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_flag;
	return (shell.flags);
}

t_shell	mltiple_arg(char *arr, t_shell *shell, t_minishell *minishell)
{
	char	*ptr;
	char	**split;
	int		i;

	ptr = expand_cmd_line(arr, minishell);
	if (quote_type(arr) || !ptr || quote_type(ptr) == 39
		|| (!ft_strcmp(shell->cmd, "export") && *arr != '$'))
		shell->flags = add_flags(arr, *shell, minishell);
	else
	{
		split = ft_split1(ptr, ' ');
		i = 0;
		while (split[i])
		{
			shell->flags = add_flags(split[i], *shell, minishell);
			i++;
		}
	}
	return (*shell);
}

t_shell	add_cmd(char ***arr, t_shell shell, t_minishell *minishell)
{
	char	*ptr;

	while (**arr)
	{
		if (***arr == '|' || ***arr == '<' || ***arr == '>')
			break ;
		if (!shell.cmd)
		{
			ptr = expand_cmd_line(**arr, minishell);
			if ((quote_type(**arr) == 34 && quote_type(ptr) != 39) || !ptr
				|| (quote_type(**arr) == 39 && quote_type(ptr) != 34)
				|| end_var(ptr))
				shell.cmd = remove_quotes(ptr);
			else
				shell = add_arg(&shell, ptr, minishell);
		}
		else
			shell = mltiple_arg(**arr, &shell, minishell);
		(*arr)++;
	}
	(*arr)--;
	return (shell);
}
