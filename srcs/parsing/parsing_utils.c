/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:55:32 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/22 06:10:19 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token(char *str)
{
	int	len;

	len = is_special(str, -1);
	if (len == 0)
	{
		while (*str && !is_special(str++, -1))
			len++;
	}
	return (len);
}

void	*init_parser(t_parser *parser, char *str)
{
	if (!str || *str == 0)
		return (NULL);
	parser->str = str;
	parser->cpy = str;
	parser->s = 0;
	parser->c = 0;
	parser->count = 0;
	return (str);
}

void	*parse_error(char *str)
{
	return (ft_puterror(ERROR_RPN_PARSING, str));
}
