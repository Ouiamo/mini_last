/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:25:41 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/11 23:06:55 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_identifier(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'
		|| (c >= '0' && c <= '9'))
		return (0);
	else
		return (1);
}

int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0' || ft_isdigit(str[0]) || str[0] == '=' || str[0] == '+')
		return (g_exit_status = export_error(str, 1));
	if (str[0] == '-')
		return (g_exit_status = export_error(str, 2));
	while ((str[i] && str[i] != '='))
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (g_exit_status = 0);
		if (check_valid_identifier(str[i]))
			return (g_exit_status = export_error(str, 1));
		i++;
	}
	return (0);
}

int	check_key(t_env *my_exp, char *key)
{
	t_env	*current;

	current = my_exp;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}
