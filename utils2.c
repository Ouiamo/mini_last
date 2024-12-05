/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:12:05 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/08 13:24:08 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long double	ft_atoi(const char *str)
{
	int			i;
	long double	nb;
	int			s;

	nb = 0;
	s = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		s = -s;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * s);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	ft_free1(char **p)
{
	int	i;

	i = 0;
	if (!p)
		return ;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return ;
}

void	free_int(t_outils *t)
{
	int	i;

	i = 0;
	while (i < t->nbr_pipes)
	{
		free(t->fd[i]);
		i++;
	}
	free(t->fd);
}

void	free_all(t_outils *exec)
{
	free_int(exec);
	free(exec->pid);
}
