/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheaks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaoulad- <oaoulad-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:44:41 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/09/21 00:20:03 by oaoulad-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cheak_prnt(char **arr)
{
	int	prnt;

	prnt = 0;
	while (*arr)
	{
		if (**arr == '(')
			prnt++;
		else if (**arr == ')')
			prnt--;
		if (prnt < 0)
			return (")");
		arr++;
	}
	if (prnt > 0)
		return ("(");
	if (prnt < 0)
		return (")");
	return (0);
}

char	*first_cheak(char **arr)
{
	if (arr[0][0] == '\0')
		return ("arr is empty");
	if (arr[0][1] && arr[0][2])
		return (*arr);
	arr++;
	if (!*arr)
		return ("newline");
	else if (*arr && (**arr == '|' || **arr == '&' || **arr == '<'
			|| **arr == '>' || **arr == '(' || **arr == ')'))
		return (*arr);
	return (NULL);
}

char	*second_cheak(char **arr)
{
	if (arr[0][0] == '\0')
		return ("arr is empty");
	if (arr[0][1])
		return (*arr);
	arr++;
	if (!*arr)
		return ("newline");
	else if (*arr && (**arr == '|' || **arr == '&' || **arr == ')'))
		return (*arr);
	return (NULL);
}
