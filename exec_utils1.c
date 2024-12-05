/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:17:18 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/12 18:17:59 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_util_1(char **cmd, int *fd, t_outils *exec)
{
	write(2, "minishell: ", 11);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	close(*fd);
	restore_in_out(exec);
	ft_malloc2(-2, 0);
	ft_malloc(-2, 0);
	exit(126);
}

void	ft_util_2(int n, int *fd, t_outils *exec)
{
	if (n == 1)
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		close(*fd);
		restore_in_out(exec);
		ft_malloc2(-2, 0);
		ft_malloc(-2, 0);
		exit(2);
	}
	else
	{
		ft_putstr_fd("minishell: .: .: is a directory\n", 2);
		close(*fd);
		restore_in_out(exec);
		ft_malloc2(-2, 0);
		ft_malloc(-2, 0);
		exit(1);
	}
}

char	*ckeck_path_cmd(char *cmd, char **paths)
{
	char	*x;
	char	*cmd1;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		x = ft_strjoin(paths[i], "/");
		cmd1 = ft_strjoin(x, cmd);
		if (access(cmd1, X_OK) == 0)
			return (cmd1);
		i++;
	}
	return (NULL);
}

void	check_special_case(char **cmd, t_outils *exec)
{
	int	fd;

	fd = open(cmd[0], __O_DIRECTORY);
	if (!ft_strncmp(cmd[0], ".", 2) && !cmd[1])
		ft_util_2(1, &fd, exec);
	else if (!ft_strncmp(cmd[0], ".", 2) && !ft_strncmp(cmd[1], ".", 2))
		ft_util_2(2, &fd, exec);
	else if (fd != -1 && (!ft_strncmp(cmd[0], "/", 1) || !ft_strncmp(cmd[0],
				"//", 2) || !ft_strncmp(cmd[0], "./", 2)
			|| !ft_strcmp(cmd[0], "../")))
		ft_util_1(cmd, &fd, exec);
	else if (fd != -1 && !exec->path)
		ft_util_1(cmd, &fd, exec);
}

char	*search_paths(char *path, t_minishell *minishell)
{
	t_env	*tmp;

	tmp = minishell->my_env;
	while (tmp)
	{
		if (ft_strcmp(path, tmp->key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
