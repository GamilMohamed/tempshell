/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:53:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/22 03:41:21 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*rpn_handle_operators(t_rpn *rpn)
{
	t_list	*op;
	t_list	*tmp;

	op = rpn->current;
	while (rpn->ops && (op->precedence <= rpn->ops->precedence))
		rpn_pop_ops(rpn);
	tmp = ft_lstnew_rpn(ft_strndup(op->content, -1), op->precedence);
	if (!tmp)
		return (NULL);
	ft_lstadd_front(&rpn->ops, tmp);
	return (tmp);
}

void	*rpn_isspecialtreatment(t_rpn *rpn)
{
	if (ft_match_list(rpn->current->content, rpn->parenthesis))
		return (rpn_handle_parenthesis(rpn));
	else
		return (rpn_handle_operators(rpn));
}

void	*rpn_generate_treatment_bis(t_rpn *rpn, int *i, int j)
{
	if (!rpn_isspecialtreatment(rpn))
		return (NULL);
	if (*i == j && rpn->prev && !ft_strncmp(rpn->prev->content, "(", 2)
		&& ft_strncmp(rpn->current->content, "(", 2)
		&& ft_match_list(rpn->current->content, rpn->specials))
		return (NULL);
	if (*i == j && rpn->prev && ft_strncmp(rpn->prev->content, ")", 2)
		&& ft_match_list(rpn->prev->content,
			rpn->specials) && !ft_strncmp(rpn->current->content, ")", 2))
		return (NULL);
	*i += ft_strlen(rpn->current->content);
	return (rpn);
}

void	*rpn_generate_treatment(t_rpn *rpn, int *i, int j)
{
	t_list	*tmp;

	rpn->prev = rpn->current;
	while (rpn->s[*i] && ft_strchr(rpn->blanks, rpn->s[*i]))
		(*i)++;
	j = *i;
	while (rpn->s[*i] && !rpn_isspecial(rpn, *i))
		(*i)++;
	if (*i != j)
	{
		if (rpn->prev && !ft_strncmp(rpn->prev->content, ")", 2))
			return (rpn->current = ft_lstlast(rpn->out), NULL);
		else if (rpn->s[*i] == '(')
			return (rpn->current = ft_lstlast(rpn->out), NULL);
		tmp = ft_lstnew_rpn(ft_strndup(rpn->s + j, *i - j), 0);
		if (!tmp)
			return (ft_puterror(FAILED_MALLOC, (char *)"rpn_generate_tr..."));
		ft_lstadd_back(&rpn->out, tmp);
	}
	if (rpn->s[*i])
	{
		if (!rpn_generate_treatment_bis(rpn, i, j))
			return (NULL);
	}
	return (rpn);
}

t_rpn	*generate_rpn(t_rpn *rpn, char *str)
{
	int		i;

	i = 0;
	init_rpn(rpn, str);
	while (rpn->s[i])
	{
		if (!rpn_generate_treatment(rpn, &i, 0))
		{
			if (rpn->current)
				ft_puterror(ERROR_RPN_PARSING, rpn->current->content);
			else
				ft_puterror(ERROR_RPN_PARSING, "(");
			return (rpn);
		}
	}
	if (rpn_popending(rpn))
		return (rpn);
	rpn->current = NULL;
	return (rpn);
}

	// printf("_________(%d)_________\nout =\t", *i);
	// ft_lstprint(rpn->out);
	// printf("ops =\t");
	// ft_lstprint(rpn->ops);
	// printf("rpn.s + i = '%s'\n", rpn->s + *i);
	// if (rpn->current)
	// 	printf("rpn.current = '%s'\n", (char *) rpn->current->content);
	// else
	// 	printf("rpn.current = (null)\n");