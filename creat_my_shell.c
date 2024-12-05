/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_my_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:31:05 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/09/29 23:49:54 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_size(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i] && !white_spaces(input[i]) && input[i] != '|'
		&& input[i] != '>' && input[i] != '<')
	{
		if (input[i] == 34 || input[i] == 39)
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
		}
		i++;
	}
	return (i);
}

int	no_quotes(char *limiter)
{
	while (*limiter)
	{
		if (*limiter == 34 || *limiter == 39)
			return (1);
		limiter++;
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int	ft_isalphanum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	return (0);
}

void	creat_my_shell(t_minishell *minishell, char **arr)
{
	int	i;
	int	nbr;

	nbr = minishell->nbr_commands;
	i = 0;
	while (*arr)
	{
		if (**arr == '|')
		{
			minishell->shell[i] = add_pipetype(*arr, minishell->shell[i]);
			i++;
		}
		else if (**arr == '<' || **arr == '>')
		{
			minishell->shell[i] = add_redir(&arr, minishell->shell[i],
					minishell);
			if (minishell->nbr_commands == -1)
				break ;
			minishell->nbr_commands = nbr;
		}
		else
			minishell->shell[i] = add_cmd(&arr, minishell->shell[i], minishell);
		if (*arr)
			arr++;
	}
}
