/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:53:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/06 19:32:57 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *ft_lstnew_rpn(void *content, int precedence)
{
	t_list	*new;
	// if (content = NULL)
		//return (error_handler(t_rpn *rpn, NULL_FAILURE));
	new = ft_lstnew(content);
	new->precedence = precedence;
	return (new);
}

void	ft_lstappendcopy(t_list **lst, t_list *copy)
{
	t_list	*new;

	while (copy)
	{
		new = ft_lstnew_rpn(ft_strndup(copy->content, -1), copy->precedence);
		ft_lstadd_back(lst, new);
		copy = copy->next;
	}
}

// checks if str exists in one of lst contents
char	*ft_match_list(char *str, t_list *lst)
{
	int	len;

	len = ft_strlen(str) + 1;
	while (lst)
	{
		if (ft_strncmp(str, (char *)lst->content, len + 1) == 0)
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}

int	is_a_closed_parenthesis(char *str)
{
	if (!ft_strncmp(str, ")", 2) || !ft_strncmp(str, "}", 2))
		return (1);
	return (0);
}