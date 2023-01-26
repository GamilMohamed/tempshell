/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 03:07:10 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/26 03:36:38 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_getdelims(char *str, t_here *here)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
			{
				i++;
				here[nb].delim = get_word(&str[i]);
				pipe(here[nb++].pipe);
			}
		}
		i++;
	}
}

static char	*openfileshd(int index, t_here *here)
{
	char	*s;
	int		fd;
	char	prompt[100];

	if (ft_strlen(here[index].delim) > 98)
		ft_strlcpy(prompt, here[index].delim, 98);
	else
		ft_strcpy(prompt, here[index].delim);
	ft_strcat(prompt, ">");
	while (1)
	{
		s = readline(prompt);
		if (!s || !ft_strcmp(s, here[index].delim))
			break ;
		ft_putendl_fd(s, here[index].pipe[1]);
		free(s);
	}
	close(here[index].pipe[1]);
	close(here[index].pipe[0]);
	return (NULL);
}

static void	exit_hd(int sig)
{
	t_data	*data;
	int		i;

	data = starton();
	ft_printf("data->here : %p\n", data->here);
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		i = -1;
		while (++i < data->nb_here)
		{
			ft_printf("is ok : %s\n", data->here[i].delim);
			close(data->here[i].pipe[1]);
			close(data->here[i].pipe[0]);
			if (data->here[i].delim != NULL)
				ft_free((void **)&data->here[i].delim);
		}
		free_all(2, 2, &data->str, &data->here, data->path, data->env);
		exit(130);
	}
}

static void	child_hd(t_data *data, char *str)
{
	int	i;

	signal(SIGINT, &exit_hd);
	i = -1;
	while (++i < data->nb_here)
		openfileshd(i, data->here);
	freestruct(data);
	free_all(2, 2, &data->here, &str, data->env, data->path);
	exit(1);
}

t_here	*here_doc(t_data *data, char *str)
{
	t_here	*here;
	int		i;
	pid_t	pid;

	data->nb_here = count_hd(str);
	if (!data->nb_here)
		return (NULL);
	data->here = ft_calloc(sizeof(t_here), data->nb_here);
	ft_getdelims(str, data->here);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	i = -1;
	if (pid == 0)
		child_hd(data, str);
	else if (pid > 0)
	{
		while (++i < data->nb_here)
			close(data->here[i].pipe[1]);
	}
	signal(SIGINT, &ctrlc);
	waitpid(pid, NULL, 0);
	return (here);
}
