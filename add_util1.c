/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_util1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 02:14:31 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/12 20:22:07 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	quote_type(char *arr)
{
	int		i;
	char	quote;

	quote = 0;
	i = -1;
	if (!arr)
		return (0);
	while (arr[++i])
	{
		if (arr[i] == 39 || arr[i] == 34)
		{
			quote = arr[i];
			break ;
		}
	}
	return (quote);
}

char	*help_quotes(char **arr, char quote, char *new, int *j)
{
	if ((**arr == 39 || **arr == 34) && **arr != quote)
		quote = **arr;
	if (**arr == quote)
	{
		(*arr)++;
		while (**arr && **arr != quote)
		{
			new[(*j)++] = **arr;
			(*arr)++;
		}
		if (**arr == quote)
			(*arr)++;
	}
	else
	{
		new[(*j)++] = **arr;
		(*arr)++;
	}
	return (new);
}

char	*remove_quotes(char *arr)
{
	char	quote;
	char	*new;
	int		j;

	if (!arr)
		return (NULL);
	quote = quote_type(arr);
	new = ft_malloc(ft_strlen(arr) + 1, 0);
	j = 0;
	while (*arr)
		new = help_quotes(&arr, quote, new, &j);
	new[j] = '\0';
	return (new);
}

int	spaces(char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
		{
			while (*str)
			{
				if (*str && *str != ' ' && *str != '\t')
					return (1);
				str++;
			}
		}
		if (*str == '\0')
			continue ;
		str++;
	}
	return (0);
}

int	ft_help(char *content, t_shell *shell, t_minishell *minishell)
{
	int	fd;

	fd = open(content, O_RDONLY);
	if (access(content, F_OK) < 0 || access(content, R_OK) < 0)
		ft_error1(content, shell, minishell);
	return (fd);
}
