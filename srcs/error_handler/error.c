/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 05:51:56 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/19 17:22:09 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_puterror(int flag, void *param)
{
	if (flag & FAILED_MALLOC)
	{
		ft_putstr_fd("Malloc failed: ", STDERR_FILENO);
		ft_putstr_fd((char *)param, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	if (flag & ERROR_RPN)
	{
		ft_putstr_fd("Error or special case: ", STDERR_FILENO);
		ft_putstr_fd((char *)param, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	if (flag & ERROR_RPN_PARSING)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd((char *)param, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	if (flag & ERROR_EXPRESSION)
		ft_putstr_fd("Expression error\n", STDERR_FILENO);
	return (NULL);
}

// int main(int ac, char **av)
// {
// 	if (ac > 2)
// 		ft_puterror(atoi(av[1]), (char *)av[2]);
// 	return (0);
// }
