/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaoulad- <oaoulad-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 02:27:08 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/09/29 11:58:20 by oaoulad-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_pwd(char *text, char *pwd, int i, int pos)
{
	char	*new;
	int		k;
	int		j;

	new = ft_malloc(ft_strlen(text) + ft_strlen(pwd) + 1, 0);
	j = 0;
	k = 0;
	while (text[j] && j < (pos - 1))
		new[k++] = text[j++];
	j = 0;
	if (pwd)
	{
		while (pwd[j])
			new[k++] = pwd[j++];
	}
	while (text[i])
		new[k++] = text[i++];
	new[k] = '\0';
	return (new);
}

char	*ft_all(char *text, int i, int j, t_minishell *minishell)
{
	if (!ft_strncmp2("PWD", &text[j], i - j))
		return (text = expand_pwd(text, minishell->save_pwd, i, j));
	else if (!ft_strncmp2("OLDPWD", &text[j], i - j))
		return (text = expand_pwd(text, minishell->save_oldpwd, i, j));
	else if (!ft_strncmp2("_", &text[j], i - j))
		return (text = expand_pwd(text, minishell->_save_last_cmd, i, j));
	return (text);
}

char	*ft_num(char *text, int pos)
{
	char	*new;
	int		i;
	int		k;

	i = 0;
	k = 0;
	new = ft_malloc(ft_strlen(text), 0);
	while (text[i] && i < pos)
	{
		new[k++] = text[i++];
	}
	if (text[i] == '$')
		i += 2;
	while (text[i])
	{
		new[k++] = text[i++];
	}
	new[k] = '\0';
	return (new);
}

char	*expand_fun(char *text, t_minishell *minishell, int i)
{
	int		j;
	char	*ptr;
	int		pos;

	pos = i;
	j = ++i;
	if (ft_isdigit(text[i]))
		text = ft_num(text, pos);
	else
	{
		while (text[i] && (ft_isalphanum(text[i]) || text[i] == '_'))
			i++;
		ptr = ft_strdup(text);
		text = ft_all(text, i, j, minishell);
		if (!ft_strcmp(ptr, text))
			text = expand_evn_var(text, minishell->my_env, j, i);
	}
	return (text);
}
