/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:12:32 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/12 17:05:48 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cheak_arr(char **arr, int *i, char **lim)
{
	char	*ptr;

	if (**arr == '|')
		return (*arr);
	*i = 0;
	while (*arr)
	{
		ptr = first_cheak(arr);
		if ((**arr == '>' || **arr == '<') && ptr)
			return (ptr);
		if (arr[0][0] == '<' && arr[0][1] == '<')
		{
			*i = 1;
			arr++;
			*lim = ft_strdup(*arr);
		}
		ptr = second_cheak(arr);
		if (**arr == '|' && ptr)
			return (ptr);
		if (*arr)
			arr++;
	}
	return (NULL);
}

int	syntax_error(char **arr)
{
	int		i;
	char	*text;
	char	*lim;
	char	*rtrn;

	rtrn = NULL;
	lim = NULL;
	i = 0;
	if (g_exit_status == 404)
		rtrn = ft_strdup("of numbers");
	else
		rtrn = cheak_arr(arr, &i, &lim);
	if (rtrn)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		(ft_putstr_fd(rtrn, 2), ft_putstr_fd("\n", 2));
		if (i == 1)
			text = get_user_text(lim);
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

void	save_last_cmd(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (minishell->nbr_commands == 1)
	{
		while (minishell->shell[0].split_cmd[i]
			&& minishell->shell[0].split_cmd[i + 1])
			i++;
		minishell->_save_last_cmd
			= ft_strdup2(minishell->shell[0].split_cmd[i]);
	}
}
