/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:27:37 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/22 20:42:40 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_waitpid(t_data *data)
{
	int	i;
	int	var;
	
	i = -1;
	while (++i < data->nbcmd)
	{
		waitpid(data->pid[i], &data->status, 0);
		if (WIFEXITED(data->status))
			data->status = WEXITSTATUS(data->status);
		if (data->status == 131 && !var++)
			ft_printf("Quit (core dumped)\n");
	}
	var = 0;
}
