/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:49:13 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/12 16:01:36 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_spisial_char(char *text, int pos)
{
	int		i;
	int		j;
	int		k;
	char	*new;
	char	*nbr;

	nbr = ft_itoa(g_exit_status);
	new = ft_malloc(ft_strlen(text) + ft_strlen(nbr), 0);
	i = 0;
	j = 0;
	while (text[i] && i < pos)
		new[j++] = text[i++];
	k = 0;
	while (nbr[k])
		new[j++] = nbr[k++];
	i += 2;
	while (text[i])
		new[j++] = text[i++];
	new[j] = '\0';
	free(nbr);
	return (new);
}

char	*no_var(char *text, int i, int j)
{
	int		k;
	char	*new;
	int		pos;

	new = ft_malloc(ft_strlen(text) + 1, 0);
	pos = j - 1;
	j = 0;
	k = 0;
	while (text[j] && j < pos)
	{
		new[k++] = text[j++];
	}
	while (text[i])
		new[k++] = text[i++];
	new[k] = '\0';
	return (new);
}

char	*ft_cpy(char *text, int j, char *new, char *value)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (text[i] && i < j - 1)
		new[k++] = text[i++];
	while (text[j] && (ft_isalphanum(text[j]) || text[j] == '_'))
		j++;
	i = 0;
	while (value[i])
		new[k++] = value[i++];
	if (quote_type(value) == 39 || quote_type(value) == 34)
		g_exit_status = 39;
	while (text[j])
		new[k++] = text[j++];
	new[k] = '\0';
	return (new);
}

char	*expand_evn_var(char *text, t_env *envp, int j, int i)
{
	char	*new;
	int		k;
	t_env	*env;

	env = envp;
	while (env)
	{
		k = ft_strncmp2(env->key, &text[j], i - j);
		if (!k)
		{
			new = ft_malloc(ft_strlen(text) + ft_strlen(env->value) + 1, 0);
			break ;
		}
		env = env->next;
	}
	if (!env)
		return (no_var(text, i, j));
	new = ft_cpy(text, j, new, env->value);
	return (new);
}

char	*herdoc_expand(char *text, t_minishell *minishell, int index)
{
	int	i;
	int	quote;

	i = 0;
	quote = 1;
	while (text[i])
	{
		if (index == 1 && text[i] == 39 && (quote == 1) && ++i)
			i = loop_text(text, i, 1, &quote);
		if (text[i] == 34)
			i = loop_text(text, i, 2, &quote);
		else if (text[i] == '$')
		{
			if (!text[i + 1])
				break ;
			else
				text = ex_pand(text, minishell, &i, quote);
			if (i == 0)
				quote = 1;
		}
		else
			i++;
	}
	return (text);
}
