/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:02:16 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/11 23:06:45 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp(t_env *my_env, t_outils *exec)
{
	int		i;
	t_env	*tmp;

	tmp = my_env;
	exec->envp = ft_malloc2(sizeof(char *) * (ft_lstsize1(tmp) + 1), 0);
	if (!exec->envp)
	{
		perror("malloc");
		return ;
	}
	i = 0;
	while (tmp)
	{
		exec->envp[i] = ft_strdup2(tmp->env_join);
		tmp = tmp->next;
		i++;
	}
	exec->envp[i] = NULL;
}

void	env_i(t_minishell *minishell)
{
	t_env	*node;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	minishell->flag = -1;
	node = ft_lstnew(ft_strdup2("PWD"), ft_strdup2(tmp));
	ft_lstadd_back(&minishell->my_env, node);
	node = ft_lstnew(ft_strdup2("SHLVL"), ft_strdup2("1"));
	ft_lstadd_back(&minishell->my_env, node);
	node = ft_lstnew(ft_strdup2("PATH"),
			ft_strdup2("/nfs/homes/wzahir/bin:/usr/local/sbin:"
				"/usr/local/bin:/usr/sbin:"
				"/usr/bin:/sbin:/bin:/usr/games:"
				"/usr/local/games:/snap/bin"));
	ft_lstadd_back(&minishell->my_env, node);
	node = ft_lstnew(ft_strdup2("_"), ft_strdup2("/usr/bin/env"));
	ft_lstadd_back(&minishell->my_env, node);
	free(tmp);
}

void	env_util(t_minishell *minishell, t_outils *exec)
{
	env_join(minishell->my_env);
	envp(minishell->my_env, exec);
	if (ft_lstsize1(minishell->my_env) < 20)
		minishell->flag = -1;
}

void	creat_my_env(t_minishell *minishell, char *key, char *value)
{
	t_env	*node;
	int		i;

	i = 0;
	if (!ft_strcmp(key, "SHLVL"))
	{
		minishell->shlvl = ft_atoi(value);
		if (minishell->shlvl >= 999 && minishell->shlvl < INT_MAX)
		{
			minishell->shlvl = i++;
			ft_putstr_fd("warning:shell level too high,resetting to 1\n", 2);
		}
		if (minishell->shlvl < 0 || minishell->shlvl >= INT_MAX)
			minishell->shlvl = 0;
		else
			minishell->shlvl += 1;
		if (value)
			value = NULL;
		value = ft_itoa(minishell->shlvl);
		node = ft_lstnew(key, ft_strdup2(value));
		free(value);
	}
	else
		node = ft_lstnew(key, ft_strdup2(value));
	ft_lstadd_back(&minishell->my_env, node);
}

void	ft_getenv(char **env, t_minishell *minishell, t_outils *exec)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	j = 0;
	i = 0;
	key = NULL;
	value = NULL;
	if (!env[i])
		env_i(minishell);
	while (env[i])
	{
		j = ft_strchr(env[i], '=');
		key = ft_substr(env[i], 0, j);
		if (!ft_strcmp(key, "_"))
			value = "/usr/bin/env";
		else
			value = ft_substr(env[i], j + 1, ft_strlen(env[i]));
		creat_my_env(minishell, key, value);
		i++;
	}
	env_util(minishell, exec);
}
