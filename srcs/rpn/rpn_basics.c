/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_basics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:53:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/22 03:37:50 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*init_rpn_aux(t_rpn *rpn, char *to_parse)
{
	if (!ft_lstappendcopy(&rpn->specials, rpn->operators))
		return (ft_puterror(FAILED_MALLOC, (char *)"init_rpn append ops"));
	if (!ft_lstappendcopy(&rpn->specials, rpn->parenthesis))
		return (ft_puterror(FAILED_MALLOC, (char *)"init_rpn append prths"));
	rpn->blanks = ft_strndup(" \t\v", 3);
	if (!rpn->blanks)
		return (ft_puterror(FAILED_MALLOC, (char *)"init_rpn blanks"));
	rpn->s = to_parse;
	return (rpn->blanks);
}

void	*init_rpn(t_rpn *rpn, char *to_parse)
{
	t_list	*tmp;

	ft_memset(rpn, 0, sizeof(*rpn));
	tmp = ft_lstnew_rpn(ft_strndup(")", -1), 0);
	if (!tmp)
		return (ft_puterror(FAILED_MALLOC, (char *)"init_rpn ')'"));
	ft_lstadd_front(&rpn->parenthesis, tmp);
	tmp = ft_lstnew_rpn(ft_strndup("(", -1), 0);
	if (!tmp)
		return (ft_puterror(FAILED_MALLOC, (char *)"init_rpn '('"));
	ft_lstadd_front(&rpn->parenthesis, tmp);
	tmp = ft_lstnew_rpn(ft_strndup("&&", -1), 1);
	if (!tmp)
		return (ft_puterror(FAILED_MALLOC, (char *)"init_rpn '&&'"));
	ft_lstadd_front(&rpn->operators, tmp);
	tmp = ft_lstnew_rpn(ft_strndup("||", -1), 1);
	if (!tmp)
		return (ft_puterror(FAILED_MALLOC, (char *)"init_rpn '||'"));
	ft_lstadd_front(&rpn->operators, tmp);
	return (init_rpn_aux(rpn, to_parse));
}

void	free_rpn(t_rpn *rpn)
{
	ft_lstclear(&rpn->out, &free);
	ft_lstclear(&rpn->ops, &free);
	ft_lstclear(&rpn->parenthesis, &free);
	ft_lstclear(&rpn->operators, &free);
	ft_lstclear(&rpn->specials, &free);
	free(rpn->blanks);
}

char	*invert_quotes(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i])
	{
		c = s[i];
		if (c == '\"' || c == '\'')
		{
			i++;
			while (s[i] && s[i] != c)
				s[i++] *= -1;
		}
		else
			i++;
	}
	return (s);
}

t_rpn	*rpn(t_rpn *rpn, char *str)
{
	if (str == NULL)
		return (NULL);
	else
	{
		invert_quotes(str);
		generate_rpn(rpn, str);
		if (rpn->current)
			return (ft_puterror(ERROR_RPN, (char *)rpn->current->content),
				free_rpn(rpn), NULL);
		return (rpn);
	}
}

// int	main(int ac, char **av)
// {
// 	t_rpn	*rpn_var;

// 	rpn_var = malloc(sizeof(*rpn_var));
// 	if (ac >= 2)
// 	{
// 		if (rpn(rpn_var, av[1]))
// 			free_rpn(rpn_var);
// 	}
// 	free(rpn_var);
// }
