/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:31:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/06 19:21:02 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblkriefft.h"
#include <stdio.h>

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		if (lst->content == NULL)
			printf("(null)");
		else
			printf("%s", (char *)lst->content);
		if (lst->next)
			printf(" -> ");
		lst = lst->next;
	}
	printf("\n");
}
