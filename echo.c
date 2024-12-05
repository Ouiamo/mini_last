/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaoulad- <oaoulad-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:04:07 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/04 23:16:50 by oaoulad-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print(int i, char **cmd)
{
	while (cmd && cmd[i])
	{
		ft_putstr_fd(cmd[i++], 1);
		if (cmd[i])
			write(1, " ", 1);
	}
}

int	ft_echo(char **cmd)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	k = 1;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 2;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] == '\0')
			k = 0;
		else
			break ;
		i++;
	}
	print(i, cmd);
	if (k == 1)
		write(1, "\n", 1);
	return (0);
}
