/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:03:16 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/12 15:40:50 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	white_spaces(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char	*turn_exp(char *var, t_minishell *minishell)
{
	char	*expand;

	herdoc_expand(var, minishell, 1);
	if (g_exit_status == 39)
		expand = herdoc_expand(var, minishell, 1);
	else
		expand = remove_quotes(herdoc_expand(var, minishell, 1));
	if (!*expand && !quote_type(var))
		return (NULL);
	if (cheak_expand(var, expand))
		return (cheak_expand(var, expand));
	return (expand);
}

int	end_var(char *exp)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(exp) - 1;
	if (i == 0 && exp[i] == '$')
		return (1);
	while (i >= 0 && exp[i])
	{
		if (exp[i] == '$')
			j++;
		else
			break ;
		i--;
	}
	if ((j % 2))
		return (1);
	return (0);
}

t_shell	add_arg(t_shell *shell, char *ptr, t_minishell *minishell)
{
	int		i;
	char	**cmd;

	cmd = ft_split1(ptr, ' ');
	if (cmd)
		shell->cmd = cmd[0];
	if (cmd[1])
	{
		i = 1;
		while (cmd[i])
		{
			shell->flags = add_flags(cmd[i], *shell, minishell);
			i++;
		}
	}
	return (*shell);
}

char	**tokensation(char *input)
{
	int		tokens;
	char	**arr;

	arr = NULL;
	tokens = count_tokens(input);
	if (tokens < 0)
		return (NULL);
	arr = ft_malloc(sizeof(char *) * (tokens + 1), 0);
	arr = cpy_to_arr(input, arr, tokens);
	return (arr);
}
