/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 06:17:04 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/23 07:07:15 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	antislash(int sig)
{
	if (sig == SIGQUIT)
		exit(131);
	if (sig == SIGINT)
		exit(130);
}

void    ctrlc(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        // replace_line("", 0);
        rl_redisplay();
    }
}