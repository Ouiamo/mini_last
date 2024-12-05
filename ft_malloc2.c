/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzahir <wzahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:34:04 by wzahir            #+#    #+#             */
/*   Updated: 2024/10/04 00:25:04 by wzahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc2(int size, void *p)
{
	static t_list	*my_collector = 0;

	if (my_collector == 0)
	{
		my_collector = malloc(sizeof(t_list));
		if (!my_collector)
			printf("i can't allocat\n");
		my_collector->content = NULL;
		my_collector->next = NULL;
	}
	if (size == -1)
		free_spicial_ptr(my_collector, p);
	else if (size == -2)
	{
		free_my_collector(my_collector);
		my_collector = 0;
	}
	else
		return (add_to_my_collector(my_collector, size));
	return (0);
}
