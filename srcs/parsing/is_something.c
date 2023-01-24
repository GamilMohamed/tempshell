/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:55:32 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/22 06:21:10 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char *str, int n)
{
	if (((*str == '<' && *(str + 1) == '<')
			|| (*str == '>' && *(str + 1) == '>')) && (n >= 2 || n < 0))
		return (2);
	else if ((*str == '<') || (*str == '>'))
		return (1);
	else
		return (0);
}

int	is_special_token(char *str, int n)
{
	if (((*str == '|' && *(str + 1) == '|')
			|| (*str == '&' && *(str + 1) == '&')
			|| (*str == '<' && *(str + 1) == '<')
			|| (*str == '>' && *(str + 1) == '>')) && (n >= 2 || n < 0))
		return (2);
	else if ((*str == '|') || (*str == '&') || (*str == '<') || (*str == '>'))
		return (1);
	else
		return (0);
}

int	is_parenthesis(char *str)
{
	if ((*str == '(') || (*str == ')'))
		return (1);
	else
		return (0);
}

int	is_special(char *str, int n)
{
	if (is_parenthesis(str))
		return (1);
	else
		return (is_special_token(str, n));
}

int	is_blank(char *str)
{
	if ((*str == ' ') || (*str == '\t') || (*str == '\v'))
		return (1);
	else
		return (0);
}
