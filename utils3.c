/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:38:50 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/02 21:26:04 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error1(char *str, t_shell *shell, t_minishell *minishell)
{
	(void)minishell;
	write(2, "minishell: ", 11);
	shell->ambiguous = 1;
	g_exit_status = 1;
	perror(str);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup2(const char *s1)
{
	int		i;
	char	*cpy;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	cpy = ft_malloc2(i + 1, 0);
	if (!cpy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	str_len;
	size_t	i;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup2(""));
	if (len > str_len - start)
		len = str_len - start;
	sub = ft_malloc2(len + 1, 0);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[len] = '\0';
	return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*str;

	if (!s1)
		return (ft_strdup2(s2));
	if (!s2)
		return (ft_strdup2(s1));
	str = ft_malloc2(ft_strlen(s1) + ft_strlen(s2) + 1, 0);
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	i = 0;
	while (s2[i])
	{
		str[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	str[ft_strlen(s1) + i] = '\0';
	return (str);
}
