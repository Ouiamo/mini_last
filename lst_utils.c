/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:51:04 by wzahir            #+#    #+#             */
/*   Updated: 2024/09/30 13:43:23 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*node;

	node = ft_malloc2(sizeof(t_env), 0);
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*node;

	if (!lst || !new)
		return ;
	node = *lst;
	if (*lst)
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
	else
		*lst = new;
}

void	ft_lstdelone(t_env *lst)
{
	if (!lst)
		return ;
	lst->key = NULL;
	lst->value = NULL;
}

int	ft_lstsize(t_list *lst)
{
	int		k;
	t_list	*node;

	node = lst;
	k = 0;
	while (node != NULL)
	{
		k++;
		node = node->next;
	}
	return (k);
}

int	ft_lstsize1(t_env *lst)
{
	int		k;
	t_env	*node;

	node = lst;
	k = 0;
	while (node != NULL)
	{
		k++;
		node = node->next;
	}
	return (k);
}
