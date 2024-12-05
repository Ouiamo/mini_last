/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:45:20 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/11 22:26:16 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_export(t_minishell *minishell)
{
	t_env	*node;
	char	*key;
	char	*value;
	t_env	*head;

	key = NULL;
	value = NULL;
	head = minishell->my_env;
	while (head)
	{
		key = ft_strdup2(head->key);
		value = ft_strdup2(head->value);
		node = ft_lstnew(key, value);
		ft_lstadd_back(&minishell->my_exp, node);
		head = head->next;
	}
	if (minishell->flag == -1)
	{
		node = ft_lstnew(ft_strdup2("OLDPWD"), NULL);
		ft_lstadd_back(&minishell->my_exp, node);
	}
}

void	swap(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = ft_strdup2(a->key);
	tmp_value = ft_strdup2(a->value);
	a->key = ft_strdup2(b->key);
	a->value = ft_strdup2(b->value);
	b->key = ft_strdup2(tmp_key);
	b->value = ft_strdup2(tmp_value);
}

void	sort_exp(t_env *my_exp)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	lptr = NULL;
	if (!my_exp)
		return ;
	while (1)
	{
		swapped = 0;
		ptr1 = my_exp;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
		if (!swapped)
			break ;
	}
}

void	print_sorted_exp(t_minishell *minishell)
{
	t_env	*head;

	sort_exp(minishell->my_exp);
	head = minishell->my_exp;
	while (head)
	{
		if ((!ft_strcmp(head->key, "PATH") && minishell->flag == -1)
			|| !ft_strcmp(head->key, "_"))
		{
			head = head->next;
			continue ;
		}
		if (!head->value)
			printf("declare -x %s\n", head->key);
		else
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
		head = head->next;
	}
}

int	export_error(char *c, int n)
{
	if (n == 1)
	{
		ft_putstr_fd("minishell: export: ˋ", STDERR_FILENO);
		ft_putstr_fd(c, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	}
	else if (n == 2)
	{
		ft_putstr_fd("minishell: export: ", STDERR_FILENO);
		ft_putstr_fd(ft_substr(c, 0, 2), 2);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		return (2);
	}
	return (1);
}
