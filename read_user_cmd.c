/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_user_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:25:59 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/12 16:52:09 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cheak_end_of_input(char *input)
{
	if (!input)
	{
		ft_malloc2(-2, 0);
		printf("exit\n");
		exit(g_exit_status);
	}
}

int	no_input(char *input)
{
	while (*input)
	{
		if (white_spaces(*input))
			input++;
		else
			break ;
	}
	if (!*input)
		return (1);
	return (0);
}

void	pars_exec(t_minishell *minishell, char **input, char **arr,
		t_outils *exec)
{
	parsing(minishell, arr);
	execution(minishell, exec);
	minishell->save_fd = -2;
	free(*input);
	ft_malloc(-2, 0);
}

void	read_user_cmd(t_minishell minishell, t_outils *exec)
{
	char	*input;
	char	**arr;

	while (1)
	{
		handling_signals(POS1, &minishell);
		input = readline("minishell $ ");
		cheak_end_of_input(input);
		if (no_input(input))
			continue ;
		add_history(input);
		arr = tokensation(input);
		if (!arr)
		{
			free(input);
			continue ;
		}
		if (syntax_error(arr))
		{
			minishell.save_fd = -2;
			(ft_malloc(-2, 0), free(input));
			continue ;
		}
		pars_exec(&minishell, &input, arr, exec);
	}
}
