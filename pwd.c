/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 21:30:50 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/12 20:31:35 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	her_util(int *fd)
{
	write(2, "minishell: ", 11);
	perror("fork");
	close(*fd);
	return (-1);
}

void	close_all(t_minishell *minishell)
{
	int		i;
	t_list	*head1;
	t_list	*head2;

	i = 0;
	while (i < minishell->nbr_commands)
	{
		head1 = minishell->shell[i].infiles;
		if (head1)
			close_fd(head1);
		head2 = minishell->shell[i].outfiles;
		if (head2)
			close_fd(head2);
		i++;
	}
}

int	ft_pwd(char **cmd, t_minishell *minishell)
{
	char	*tmp;

	if (cmd[1] && cmd[1][0] == '-')
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putstr_fd(ft_substr(cmd[1], 0, 2), 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		ft_putstr_fd(tmp, 1);
		ft_putstr_fd("\n", 1);
		free(tmp);
	}
	else
	{
		ft_putstr_fd(minishell->save_pwd, 1);
		write(1, "\n", 1);
		free(tmp);
	}
	return (0);
}

void	sheck_warning_shlvl(char *key, char *value)
{
	if (!ft_strcmp(key, "SHLVL") && (ft_atoi(value) < INT_MIN
			|| ft_atoi(value) == 2147483648))
	{
		ft_putstr_fd("minishell: warning: shell level too high,"
			"resetting to 1\n", 2);
	}
}
