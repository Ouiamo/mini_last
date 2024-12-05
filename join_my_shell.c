/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_my_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaoulad- <oaoulad-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:41:40 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/09/08 09:41:24 by oaoulad-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*join;

	i = 0;
	j = 0;
	join = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 2, 0);
	while (s1[i])
		join[j++] = s1[i++];
	join[j++] = ' ';
	i = 0;
	while (s2[i])
		join[j++] = s2[i++];
	join[j] = '\0';
	return (join);
}

char	*join_my_command(t_shell shell)
{
	t_list	*flags;
	char	*my_command;

	if (!shell.flags)
		return (shell.cmd);
	flags = shell.flags;
	my_command = my_join(shell.cmd, flags->content);
	flags = flags->next;
	while (flags)
	{
		my_command = my_join(my_command, flags->content);
		flags = flags->next;
	}
	return (my_command);
}

void	join_my_shell(t_minishell *minishell, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		minishell->shell[i].full_commnad = join_my_command(minishell->shell[i]);
		i++;
	}
}
