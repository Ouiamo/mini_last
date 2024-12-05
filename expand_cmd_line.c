/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:27:45 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/12 15:52:34 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_last(char *text, int i)
{
	int		j;
	int		k;
	char	*new;

	new = ft_malloc(ft_strlen(text), 0);
	j = 0;
	k = 0;
	while (text[j] && j < i)
		new[k++] = text[j++];
	j++;
	while (text[j])
		new[k++] = text[j++];
	new[k] = '\0';
	return (new);
}

char	*ex_pand(char *text, t_minishell *minishell, int *i, int quote)
{
	if (text[*i + 1] == '$')
		*i += 2;
	else
		text = rest_of_exp(text, minishell, i, quote);
	return (text);
}

char	*new_expand(char *expand)
{
	int		i;
	char	**new;
	char	*retun;

	i = 0;
	new = ft_split1(expand, '\n');
	retun = NULL;
	if (new)
	{
		retun = my_join(new[0], new[1]);
		i = 2;
		while (new[i])
		{
			retun = my_join(retun, new[i]);
			i++;
		}
	}
	return (retun);
}

char	*cheak_expand(char *var, char *expand)
{
	if (ft_strchr(expand, '\n') > -1)
	{
		if (*var == '$')
			return (new_expand(expand));
	}
	return (expand);
}

char	*expand_cmd_line(char *var, t_minishell *minishell)
{
	int	i;
	int	double_quote;

	i = -1;
	double_quote = -1;
	while (var[++i])
	{
		if (var[i] == 39 && double_quote == -1 && ++i)
			while (var[i] && var[i] != 39)
				i++;
		if (!var[i])
			return (remove_quotes(var));
		if (var[i] == 34)
			double_quote *= -1;
		if (var[i] == '$')
			return (turn_exp(var, minishell));
	}
	return (remove_quotes(var));
}
