/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:53:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/14 17:32:45 by lkrief           ###   ########.fr       */
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
		{
			rpn->current = lst;
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

char	*rpn_handle_parenthesis(t_rpn *rpn)
{
	char	*parenthesis;

	parenthesis = rpn->current->content;
	if (!ft_strncmp(parenthesis, "(", 2))
		ft_lstadd_front(&rpn->ops, ft_lstnew_rpn(ft_strndup(")", -1), 0));
	else if (!ft_strncmp(parenthesis, "{", 2))
		ft_lstadd_front(&rpn->ops, ft_lstnew_rpn(ft_strndup("}", -1), 0));
	else if (!ft_strncmp(parenthesis, ")", 2))
	{
		while (rpn->ops && ft_strncmp(rpn->ops->content, ")", 2))
			rpn_pop_ops(rpn);
		if (!rpn->ops)
			return (parenthesis);
		else
			rpn_pop_opsdel(rpn);
	}
	else if (!ft_strncmp(parenthesis, "}", 2))
	{
		while (rpn->ops && ft_strncmp(rpn->ops->content, "}", 2))
			rpn_pop_ops(rpn);
		if (!rpn->ops)
			return (parenthesis);
		else
			rpn_pop_opsdel(rpn);
	}
	return (NULL);
}

char	*rpn_handle_operators(t_rpn *rpn)
{
	t_list	*op;

	op = rpn->current;
	while (rpn->ops && (op->precedence <= rpn->ops->precedence))
		rpn_pop_ops(rpn);
	ft_lstadd_front(&rpn->ops, ft_lstnew_rpn(ft_strndup(op->content, -1), op->precedence));
	return (NULL);
}

char	*rpn_isspecialtreatment(t_rpn *rpn)
{
	char	*special;

	special = ft_match_list(rpn->current->content, rpn->parenthesis);
	if (special)
		return (rpn_handle_parenthesis(rpn));
	else
		return (rpn_handle_operators(rpn));
}

t_rpn	*generate_rpn(t_rpn *rpn, char *str)
{
	int		i;
	int		j;

	i = 0;
	init_rpn(rpn, str);
	while (rpn->s[i])
	{
		rpn->check = rpn->current;
		while (rpn->s[i] && ft_strchr(rpn->blanks, rpn->s[i]))
			i++;
		j = i;
		while (rpn->s[i] && !rpn_isspecial(rpn, i))
			i++;
		if (i != j)
			ft_lstadd_back(&rpn->out, ft_lstnew_rpn(ft_strtrim(ft_strndup(str + j, i - j), rpn->blanks), 0));
		if (i != j && rpn->check && is_a_closed_parenthesis(rpn->check->content))
		{
			rpn->current = ft_lstlast(rpn->out);
			return (rpn);
		}
		if (rpn->s[i])
		{
			if (rpn_isspecialtreatment(rpn))
				return (rpn);
			i += ft_strlen(rpn->current->content);
		}
	}
	if (rpn_popending(rpn))
		return (rpn);
	rpn->current = NULL;
	return (rpn);
}
