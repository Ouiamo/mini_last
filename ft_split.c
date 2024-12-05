/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:29:28 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/09/28 12:42:26 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

static char	*new_str(const char *str, int *index, char c)
{
	int		i;
	size_t	str_len;
	char	*cpy;

	while (str[*index] == c)
		(*index)++;
	i = *index;
	str_len = 0;
	while (str[i] && str[i] != c)
	{
		str_len++;
		i++;
	}
	cpy = ft_malloc(sizeof(char) * (str_len + 1), 0);
	if (!cpy)
		return (NULL);
	i = 0;
	while (str[*index] && str[*index] != c)
		cpy[i++] = str[(*index)++];
	cpy[i] = '\0';
	return (cpy);
}

char	**free_memory(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		index;
	int		count;
	char	**tab;

	i = 0;
	index = 0;
	if (!s)
		return (NULL);
	count = count_word(s, c);
	tab = ft_malloc2((sizeof(char *) * (count + 1)), 0);
	if (!tab)
		return (NULL);
	while (i < count)
	{
		tab[i] = new_str(s, &index, c);
		if (!tab[i])
			return (free_memory(tab));
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	**ft_split1(char const *s, char c)
{
	int		i;
	int		index;
	int		count;
	char	**tab;

	i = 0;
	index = 0;
	if (!s)
		return (NULL);
	count = count_word(s, c);
	tab = ft_malloc((sizeof(char *) * (count + 1)), 0);
	if (!tab)
		return (NULL);
	while (i < count)
	{
		tab[i] = new_str(s, &index, c);
		if (!tab[i])
			return (free_memory(tab));
		i++;
	}
	tab[i] = 0;
	return (tab);
}
