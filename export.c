/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:34:07 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/07 21:31:37 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exist_value(t_minishell *minishell, char *key, char *value)
{
	t_env	*head;

	head = minishell->my_exp;
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
		{
			head->value = NULL;
			head->key = NULL;
			head->key = ft_strdup2(key);
			head->value = ft_strdup2(value);
			if (!ft_strcmp(key, "PWD"))
				minishell->save_pwd = ft_strdup2(value);
			else if (!ft_strcmp(key, "OLDPWD"))
				minishell->save_oldpwd = ft_strdup2(value);
			return (0);
		}
		head = head->next;
	}
	return (1);
}

int	add_value(t_minishell *minishell, char *key, char *value)
{
	t_env	*head;

	head = minishell->my_exp;
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
		{
			head->value = ft_strjoin(head->value, value);
			return (0);
		}
		head = head->next;
	}
	return (1);
}

void	creat_node(t_minishell *minishell, char *key, char *value)
{
	t_env	*node;

	node = ft_lstnew(key, value);
	ft_lstadd_back(&minishell->my_exp, node);
	if (!ft_strcmp(key, "PWD"))
	{
		if (minishell->save_pwd)
			minishell->save_pwd = NULL;
		minishell->save_pwd = ft_strdup2(value);
	}
	else if (!ft_strcmp(key, "OLDPWD"))
	{
		if (minishell->save_oldpwd)
			minishell->save_oldpwd = NULL;
		minishell->save_oldpwd = ft_strdup2(value);
	}
}

void	util_exp(char *cmd, t_minishell *minishell)
{
	char	*key;
	char	*value;
	int		j;

	j = ft_strchr(cmd, '=');
	if (j >= 0 && ft_strchr(cmd, '+') >= 0 && ft_strchr(cmd, '+') < j)
	{
		key = ft_substr(cmd, 0, ft_strchr(cmd, '+'));
		value = ft_substr(cmd, j + 1, ft_strlen(cmd));
		if (add_value(minishell, key, value))
			creat_node(minishell, key, value);
	}
	else if (j >= 0)
	{
		key = ft_substr(cmd, 0, j);
		value = ft_substr(cmd, j + 1, ft_strlen(cmd));
		if (exist_value(minishell, key, value))
			creat_node(minishell, key, value);
	}
	else
	{
		if (!check_key(minishell->my_exp, cmd))
			creat_node(minishell, ft_strdup2(cmd), NULL);
	}
}

int	ft_export(t_minishell *minishell, char **cmd, t_outils *exec)
{
	int	i;

	i = 1;
	if (!cmd[i])
		print_sorted_exp(minishell);
	else
	{
		while (cmd[i])
		{
			if (!check_arg(cmd[i]))
				util_exp(cmd[i], minishell);
			i++;
		}
		env_from_exp(minishell, exec);
	}
	return (g_exit_status);
}
