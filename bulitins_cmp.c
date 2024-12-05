/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulitins_cmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:58:00 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/12 13:40:39 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_env(char *c, int n)
{
	if (n == 1)
	{
		ft_putstr_fd("env: ‘", STDERR_FILENO);
		ft_putstr_fd(c, STDERR_FILENO);
		ft_putstr_fd("’: No such file or directory\n", 2);
	}
	else if (n == 2)
	{
		ft_putstr_fd("env", STDERR_FILENO);
		ft_putstr_fd(": invalid option -- '", STDERR_FILENO);
		ft_putstr_fd(ft_substr(c, 1, 2), 2);
		write(2, "\'\n", 2);
		return (125);
	}
	return (127);
}

void	env_join(t_env *my_env)
{
	char	*tmp;
	t_env	*head;

	head = my_env;
	while (head)
	{
		tmp = ft_strjoin(head->key, "=");
		head->env_join = ft_strjoin(tmp, head->value);
		head = head->next;
	}
}

int	ft_env(t_minishell *minishell, char **cmd, t_outils *exec)
{
	t_env	*tmp;

	env_join(minishell->my_env);
	envp(minishell->my_env, exec);
	tmp = NULL;
	if (!cmd[1])
	{
		tmp = minishell->my_env;
		while (tmp)
		{
			if (!tmp->value || (!ft_strcmp(tmp->key, "PATH")
					&& minishell->flag == -1))
				tmp = tmp->next;
			else
			{
				printf("%s\n", tmp->env_join);
				tmp = tmp->next;
			}
		}
	}
	else if (cmd[1][0] == '-')
		return (error_env(cmd[1], 2));
	else
		return (error_env(cmd[1], 1));
	return (0);
}

void	env_from_exp(t_minishell *minishell, t_outils *exec)
{
	t_env	*node;
	char	*key;
	char	*value;
	t_env	*head;

	head = minishell->my_exp;
	minishell->my_env = NULL;
	while (head)
	{
		if (head->value)
		{
			key = ft_strdup2(head->key);
			value = ft_strdup2(head->value);
			sheck_warning_shlvl(key, value);
			node = ft_lstnew(key, value);
			ft_lstadd_back(&minishell->my_env, node);
		}
		head = head->next;
	}
	env_join(minishell->my_env);
	envp(minishell->my_env, exec);
}

int	builtins(t_minishell *minishell, int i, t_outils *exec)
{
	if (ft_strcmp(minishell->shell[i].cmd, "exit") == 0)
	{
		ft_exit(minishell->shell[i].split_cmd, minishell);
		return (g_exit_status);
	}
	else if (ft_strcmp(minishell->shell[i].cmd, "cd") == 0)
		return (g_exit_status = ft_cd(minishell,
				minishell->shell[i].split_cmd));
	else if (ft_strcmp(minishell->shell[i].cmd, "echo") == 0)
		return (g_exit_status = ft_echo(minishell->shell[i].split_cmd));
	else if (ft_strcmp(minishell->shell[i].cmd, "env") == 0)
		return (g_exit_status = ft_env(minishell, minishell->shell[i].split_cmd,
				exec));
	else if (ft_strcmp(minishell->shell[i].cmd, "export") == 0)
		return (ft_export(minishell, minishell->shell[i].split_cmd, exec));
	else if (ft_strcmp(minishell->shell[i].cmd, "unset") == 0)
		return (g_exit_status = ft_unset(minishell,
				minishell->shell[i].split_cmd));
	else if (ft_strcmp(minishell->shell[i].cmd, "pwd") == 0)
		return (g_exit_status = ft_pwd(minishell->shell[i].split_cmd,
				minishell));
	else
		return (-1);
}
