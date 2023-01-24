/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:27:37 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/24 17:23:11 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_waitpid(t_data *data)
{
	int	i;
	int	var;

	i = -1;
	var = 0;
	while (++i < data->nbcmd)
	{
		waitpid(data->pid[i], &data->status, 0);
		if (WIFEXITED(data->status))
			data->status = WEXITSTATUS(data->status);
		if (data->status == 131 && !var++)
			ft_printf("Quit (core dumped)\n");
	}
}

void	dupnclose(int fd, int std)
{
	dup2(fd, std);
	close(fd);
}

int	matching(char *match)
{
	int					i;
	static const char	*matchs[7] = {
		"cd", "echo", "exit", "export", "pwd", "unset", "env"};

	if (!match)
		return (0);
	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(matchs[i++], match))
			return (1);
	}
	return (0);
}
