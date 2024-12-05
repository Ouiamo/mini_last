/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 10:23:28 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/11 01:24:50 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(int i, char *args)
{
	while ((args[i] >= 9 && args[i] <= 13) || args[i] == ' ')
	{
		i++;
		if (args[i] == '\0')
			return (1);
		if (!((args[i] >= 9 && args[i] <= 13) || args[i] == ' '))
			return (0);
	}
	return (0);
}

int	is_str_digit(char *args)
{
	int	i;

	i = 0;
	while ((args[i] >= 9 && args[i] <= 13) || args[i] == ' ')
		i++;
	if (args[i] == '-' || args[i] == '+')
		i++;
	if (args[i] == '\0')
		return (0);
	while (args[i])
	{
		if (ft_isdigit(args[i]) == 0)
			return (skip_spaces(i, args));
		i++;
	}
	return (1);
}

void	free_malloc(void)
{
	ft_malloc(-2, 0);
	ft_malloc2(-2, 0);
}

void	print_msg(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_malloc();
	exit(g_exit_status = 2);
}

void	ft_exit(char **cmd, t_minishell *minishell)
{
	long long	nbr;

	if (minishell->nbr_commands == 1)
		ft_putstr_fd("exit\n", 2);
	if (!cmd[1])
	{
		free_malloc();
		exit(g_exit_status);
	}
	else if (is_str_digit(cmd[1]) && !(ft_atoi(cmd[1]) < LLONG_MIN
			|| ft_atoi(cmd[1]) > LLONG_MAX) && !cmd[2])
	{
		nbr = ft_atoi(cmd[1]);
		free_malloc();
		exit(g_exit_status = nbr);
	}
	else if (is_str_digit(cmd[1]) && cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	else
		print_msg(cmd[1]);
}
