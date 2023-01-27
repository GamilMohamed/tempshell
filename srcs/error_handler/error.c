/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 05:51:56 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/27 14:46:50 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_puterror2(int flag, void *param)
{
	if (flag & ERROR_CD_BUILTIN)
	{
		ft_putstr_fd("bash: cd: ", STDERR_FILENO);
		ft_putstr_fd((char *)param, STDERR_FILENO);
		if (errno == EACCES || errno == ENOENT)
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		else if (errno == ENOTDIR)
			ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		else
			ft_putstr_fd(": Error changing directory\n", STDERR_FILENO);
	}
	if (flag & ERROR_EXPORT_BUILTIN)
	{
		ft_putstr_fd("bash: export: `", STDERR_FILENO);
		ft_putstr_fd((char *)param, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	}
	return (NULL);
}

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
		ft_putstr_fd("bash: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd((char *)param, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	if (flag & ERROR_EXPRESSION)
		ft_putstr_fd("Expression error\n", STDERR_FILENO);
	return (ft_puterror2(flag, param));
}

// int main(int ac, char **av)
// {
// 	if (ac > 2)
// 		ft_puterror(atoi(av[1]), (char *)av[2]);
// 	return (0);
// }
