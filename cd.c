/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:12:14 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/11 02:12:04 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(char *error, int i)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (i == 1)
		perror(error);
	else if (i == 2)
		ft_putstr_fd("too many arguments\n", 2);
	else if (i == 3)
	{
		ft_putstr_fd(ft_substr(error, 0, 2), 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	else if (i == 4)
		ft_putstr_fd("HOME not set\n", 2);
	return (1);
}

void	change_value(t_minishell *minishell, char *key, char *new_value)
{
	t_env	*head;
	t_env	*head1;

	head = minishell->my_env;
	head1 = minishell->my_exp;
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
		{
			head->value = NULL;
			head->value = ft_strdup2(new_value);
			break ;
		}
		head = head->next;
	}
	while (head1)
	{
		if (ft_strcmp(head1->key, key) == 0)
		{
			head1->value = NULL;
			head1->value = ft_strdup2(new_value);
			break ;
		}
		head1 = head1->next;
	}
}

char	*search_key(t_env *my_env, char *key)
{
	t_env	*current;

	current = my_env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	pwd_home(t_minishell *minishell)
{
	char	*pwd;

	pwd = search_key(minishell->my_env, "HOME");
	if (!pwd)
		return (error(minishell->shell->split_cmd[1], 4));
	if (chdir(pwd) < 0)
		return (error(pwd, 1));
	minishell->save_pwd = ft_strdup2(pwd);
	change_value(minishell, "PWD", pwd);
	return (0);
}

int	ft_cd(t_minishell *minishell, char **cmd)
{
	char	*pwd;

	if (cmd[1] && cmd[2])
		return (error(cmd[1], 2));
	if (cmd[1] && cmd[1][0] == '-')
		return (error(cmd[1], 3));
	if (cmd[1] && !ft_strcmp(cmd[1], ""))
		return (0);
	minishell->save_oldpwd = ft_strdup2(minishell->save_pwd);
	change_value(minishell, "OLDPWD", minishell->save_oldpwd);
	if (!cmd[1])
		return (pwd_home(minishell));
	else
	{
		if (chdir(cmd[1]) < 0)
			return (error(cmd[1], 1));
	}
	pwd = getcwd(NULL, 0);
	minishell->save_pwd = ft_strdup2(pwd);
	change_value(minishell, "PWD", pwd);
	free (pwd);
	return (0);
}
