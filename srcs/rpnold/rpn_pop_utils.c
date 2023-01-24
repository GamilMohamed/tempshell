/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_pop_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:53:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/06 05:15:29 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rpn_pop_ops(t_rpn *rpn)
{
	t_list	*tmp;
	if (rpn->ops)
	{
		tmp = rpn->ops;
		rpn->ops = rpn->ops->next;
		tmp->next = NULL;
		ft_lstadd_back(&rpn->out, tmp);
	}
	return (NULL);
}

char	*rpn_popending(t_rpn *rpn)
{
	t_list	*tmp;
	while (rpn->ops)
	{
		// if (rpn->)
		if (ft_match_list(rpn->ops->content, rpn->parenthesis))
		{
			if (((char *)rpn->ops->content)[0] == ')')
				((char *)rpn->ops->content)[0] = '(';
			else if (((char *)rpn->ops->content)[0] == '}')
				((char *)rpn->ops->content)[0] = '{';
			rpn->current = rpn->ops;
			return (rpn->ops->content);
		}
		tmp = rpn->ops;
		rpn->ops = rpn->ops->next;
		tmp->next = NULL;
		ft_lstadd_back(&rpn->out, tmp);
	}
	return (NULL);
}

void	rpn_pop_opsdel(t_rpn *rpn)
{
	t_list	*tmp;

	if (!rpn->ops)
		return ;
	else
	{
		tmp = rpn->ops->next;
		free (rpn->ops->content);
		free (rpn->ops);
		rpn->ops = tmp;
	}
}
