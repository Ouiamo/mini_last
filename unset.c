/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:31:09 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/11 21:41:00 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_unset(char *str)
{
	ft_putstr_fd("minishell: unset: ", 2);
	ft_putstr_fd(ft_substr(str, 0, 2), 2);
	ft_putstr_fd(": invalid option\n", 2);
	return (2);
}

void	delete(t_env **head, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *head;
	prev = NULL;
	if (tmp && ft_strcmp(tmp->key, key) == 0)
	{
		*head = tmp->next;
		ft_lstdelone(tmp);
		return ;
	}
	while (tmp && ft_strcmp(tmp->key, key) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	prev->next = tmp->next;
	ft_lstdelone(tmp);
}

int	search(t_env *ptr, char *key)
{
	t_env	*current;

	current = ptr;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

int	ft_unset(t_minishell *minishell, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (cmd[1] && cmd[1][0] == '-')
			return (error_unset(cmd[1]));
		if (ft_strcmp(cmd[i], "_") == 0)
		{
			i++;
			continue ;
		}
		if (!ft_strcmp(cmd[i], "PWD"))
			minishell->save_pwd = NULL;
		if (!ft_strcmp(cmd[i], "OLDPWD"))
			minishell->save_oldpwd = NULL;
		if (search(minishell->my_exp, cmd[i]))
			delete (&minishell->my_exp, cmd[i]);
		if (search(minishell->my_env, cmd[i]))
			delete (&minishell->my_env, cmd[i]);
		i++;
	}
	return (0);
}
