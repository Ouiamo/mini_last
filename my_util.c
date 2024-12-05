/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:18:16 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/12 14:51:22 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop_text(char *text, int i, int pos, int *quote)
{
	if (pos == 1)
	{
		if (!text[i])
			return (i - 1);
		while (text[i] && text[i] != 39)
			i++;
	}
	else if (pos == 2)
	{
		*quote *= -1;
		i++;
	}
	return (i);
}

char	*rest_of_exp(char *text, t_minishell *minishell, int *i, int quote)
{
	int	pos;

	pos = *i;
	if (text[*i + 1] != '$')
	{
		if (quote == 1 && (text[*i + 1] == 34 || text[*i + 1] == 39))
			text = ft_last(text, *i);
		else if (text[*i + 1] == '?')
			text = expand_spisial_char(text, pos);
		else if (!ft_isalphanum(text[*i + 1]) && text[*i + 1] != '_')
		{
			*i += 1;
			return (text);
		}
		else if (ft_isalphanum(text[*i + 1]) || text[*i + 1] == '_')
			text = expand_fun(text, minishell, *i);
		*i = 0;
	}
	else
		(*i)++;
	return (text);
}
