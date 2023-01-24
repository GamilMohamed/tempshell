/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:55:32 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/22 07:04:24 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*is_special_parsing(t_parser *p)
{
	if (*(p->str) == OPENED_PRTHS)
	{
		p->count++;
		if (is_special(p->cpy, p->c))
			return (*(p->cpy + p->c) = '\0', parse_error(p->cpy));
	}
	else if (*(p->str) == CLOSED_PRTHS)
	{
		p->count--;
		if (p->count < 0)
			return (*(p->str + p->s) = '\0', parse_error(p->str));
		if (!is_special(p->cpy, p->c))
			return (*(p->cpy + p->c) = '\0', parse_error(p->cpy));
	}
	else if (is_redirection(p->str, p->s) && is_special(p->cpy, p->c))
		return (*(p->cpy + p->c) = '\0', parse_error(p->cpy));
	else if (*(p->cpy) != OPENED_PRTHS && !is_redirection(p->cpy, p->c)
		&& is_special(p->cpy, p->c))
		return (*(p->cpy + p->c) = '\0', parse_error(p->cpy));
	return (p);
}

void	*is_not_special_parsing(t_parser *p)
{
	if (*(p->cpy) == OPENED_PRTHS)
	{
		p->cpy = p->cpy + p->c;
		while (is_blank(p->cpy))
			p->cpy++;
		p->c = get_token(p->cpy);
		if (!p->c)
			return (*(p->cpy + p->c) = '\0', parse_error("newline"));
		return (*(p->cpy + p->c) = '\0', parse_error(p->cpy));
	}
	return (p);
}

void	*next_is_null_parsing(t_parser *p)
{
	if (*(p->str) == CLOSED_PRTHS)
	{
		p->count--;
		if (p->count != 0)
			return (*(p->str + p->s) = '\0', parse_error(p->str));
	}
	else if (is_redirection(p->str, p->s))
		return (*(p->str + p->s) = '\0', parse_error("newline"));
	else if (is_special(p->str, p->s))
		return (*(p->str + p->s) = '\0', parse_error(p->str));
	if (p->count != 0)
		return (*(p->str + p->s) = '\0', parse_error(p->str));
	return (p);
}

void	*parse_check(t_parser *p)
{
	if (!p->c)
		return (next_is_null_parsing(p));
	else if (is_special(p->str, p->s))
		return (is_special_parsing(p));
	else
		return (is_not_special_parsing(p));
}

char	*parsing(char *str)
{
	t_parser	parser;

	if (!init_parser(&parser, str))
		return (NULL);
	while (is_blank(parser.str))
		parser.str++;
	parser.s = get_token(parser.str);
	while (parser.str && parser.s > 0)
	{
		parser.cpy = parser.str + parser.s;
		while (is_blank(parser.cpy))
			parser.cpy++;
		parser.c = get_token(parser.cpy);
		if (!parse_check(&parser))
			return (NULL);
		parser.str = parser.cpy;
		parser.s = parser.c;
	}
	return (str);
}

// int main(int ac, char **av)
// {
// 	if (ac)
// 	{
// 		if (av[1])
// 			printf("%s\n", av[1]);
// 		else
// 			printf("(null)\n");
// 		if (parsing(av[1]))
// 			printf("VALID STRING\n");
// 	}
// }