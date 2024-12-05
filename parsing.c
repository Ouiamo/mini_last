/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaoulad- <oaoulad-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:12:27 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/04 23:27:51 by oaoulad-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_new(char *cmd, t_list *args)
{
	char	**ptr;
	int		arg_size;
	t_list	*tmp;
	int		i;

	tmp = args;
	arg_size = ft_lstsize(tmp);
	ptr = ft_malloc(sizeof(char *) * (arg_size + 2), 0);
	i = 0;
	ptr[i++] = ft_strdup(cmd);
	while (tmp)
	{
		ptr[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	ptr[i] = NULL;
	return (ptr);
}

int	nbr_commands(char **arr)
{
	int	i;

	i = 1;
	while (*arr)
	{
		if (**arr == '|')
			i++;
		arr++;
	}
	return (i);
}

void	initial_my_shell(t_minishell *minishell, char **arr)
{
	int	i;

	i = nbr_commands(arr);
	minishell->nbr_commands = i;
	minishell->shell = ft_malloc(sizeof(t_shell) * (i + 1), 0);
	while (i > -1)
	{
		minishell->shell[i].pipe_type = 0;
		minishell->shell[i].cmd = NULL;
		minishell->shell[i].flags = NULL;
		minishell->shell[i].outfiles = NULL;
		minishell->shell[i].infiles = NULL;
		minishell->shell[i].split_cmd = NULL;
		minishell->shell[i].ambiguous = 0;
		i--;
	}
}

void	split_full_command(t_minishell *minishell, int n)
{
	int	i;

	if (n < 0)
		return ;
	i = 0;
	while (i < n)
	{
		minishell->shell[i].split_cmd = ft_new(minishell->shell[i].cmd,
				minishell->shell[i].flags);
		i++;
	}
}

void	parsing(t_minishell *minishell, char **arr)
{
	initial_my_shell(minishell, arr);
	creat_my_shell(minishell, arr);
	split_full_command(minishell, minishell->nbr_commands);
}
