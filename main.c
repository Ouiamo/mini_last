/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:08:29 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/12 16:38:51 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(int ac, char **av, char **env)
{
	t_outils	exec;
	t_minishell	minishell;

	(void)av;
	if (ac == 1)
	{
		minishell.my_env = NULL;
		g_exit_status = 0;
		minishell.my_exp = NULL;
		minishell._save_last_cmd = ft_strdup2("]");
		minishell.flag = 0;
		minishell.save_fd = -2;
		ft_getenv(env, &minishell, &exec);
		my_export(&minishell);
		minishell.save_oldpwd = ft_strdup2(search_key(minishell.my_env,
					"OLDPWD"));
		minishell.save_pwd = ft_strdup2(search_key(minishell.my_env, "PWD"));
		read_user_cmd(minishell, &exec);
		ft_malloc2(-2, 0);
		exit(g_exit_status);
	}
	return (0);
}
