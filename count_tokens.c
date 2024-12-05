/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaoulad- <oaoulad-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:14:58 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/09/20 23:25:09 by oaoulad-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handel_quotes(char *input)
{
	char	quote;

	quote = *input;
	input++;
	while (*input && *input != quote)
		input++;
	if (*input != quote)
	{
		printf("UNCLOSED QUOTE\n");
		return (NULL);
	}
	else if (*input == quote)
		input++;
	return (input);
}

char	*handel_pipe_redir(char *input)
{
	char	symbol;

	symbol = *input;
	while (*input == symbol)
		input++;
	return (input);
}

char	*handel_normal_arg(char *input)
{
	while (*input && !white_spaces(*input) && *input != '|' && *input != '>'
		&& *input != '<')
	{
		if (*input == 34 || *input == 39)
		{
			input = handel_quotes(input);
			if (!input)
				return (NULL);
		}
		else
			input++;
	}
	return (input);
}

int	count_tokens(char *input)
{
	int	count;

	count = 0;
	while (white_spaces(*input))
		input++;
	if (!*input)
		return (0);
	while (*input)
	{
		if (*input == '|' || *input == '>' || *input == '<')
			input = handel_pipe_redir(input);
		else
		{
			input = handel_normal_arg(input);
			if (!input)
				return (-1);
		}
		while (white_spaces(*input))
			input++;
		count++;
	}
	return (count);
}
