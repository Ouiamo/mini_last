/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:50:22 by oaoulad-          #+#    #+#             */
/*   Updated: 2024/10/04 00:21:56 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_negative(int *n, unsigned int *nbr, size_t *len)
{
	if (*n <= 0)
	{
		*nbr = -(*n);
		(*len)++;
	}
}

static int	length(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*revrs_str(char *str)
{
	int		first;
	int		last;
	char	swap;

	first = 0;
	last = ft_strlen(str) - 1;
	while (first < last)
	{
		swap = str[first];
		str[first] = str[last];
		str[last] = swap;
		first++;
		last--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*number;
	size_t			i;
	size_t			len;
	unsigned int	nbr;

	i = 0;
	nbr = n;
	len = 0;
	is_negative(&n, &nbr, &len);
	len += length(n);
	number = malloc(sizeof(char) * (len + 1));
	if (!number)
		return (NULL);
	if (n == 0)
		number[i++] = '0';
	while (nbr)
	{
		number[i++] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	if (n < 0)
		number[i++] = '-';
	number[i] = 0;
	return (revrs_str(number));
}
