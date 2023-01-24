/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_algo_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:53:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/22 03:37:20 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rpn_isspecial(t_rpn *rpn, int i)
{
	int		len;
	t_list	*lst;

	rpn->current = NULL;
	lst = rpn->specials;
	while (lst)
	{
		len = ft_strlen(lst->content);
		if (ft_strncmp(rpn->s + i, lst->content, len) == 0)
			return (rpn->current = lst, 1);
		lst = lst->next;
	}
	return (0);
}

void	*rpn_handle_parenthesis(t_rpn *rpn)
{
	char	*parenthesis;
	t_list	*tmp;

	parenthesis = rpn->current->content;
	if (!ft_strncmp(parenthesis, "(", 2))
	{
		tmp = ft_lstnew_rpn(ft_strndup(")", -1), 0);
		if (!tmp)
			return (ft_puterror(FAILED_MALLOC, (char *)"rpn_handle_prthss"));
		ft_lstadd_front(&rpn->ops, tmp);
	}
	else if (!ft_strncmp(parenthesis, ")", 2))
	{
		while (rpn->ops && ft_strncmp(rpn->ops->content, ")", 2))
			rpn_pop_ops(rpn);
		if (!rpn->ops)
			return (ft_puterror(ERROR_EXPRESSION, NULL));
		else
			rpn_pop_opsdel(rpn);
	}
	return (parenthesis);
}
