/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 03:07:10 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/24 12:24:53 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_word(char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i] && !ft_strchr("><|", str[i])))
	{
		i++;
		r++;
	}
	return (r);
}

char	*get_word(char *str)
{
	int		i;
	int		r;
	char	*new;

	new = malloc(get_len_word(str) + 1);
	i = 0;
	r = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i]) && !ft_strchr("><|", str[i]))
		new[r++] = str[i++];
	new[r] = 0;
	return (new);
}

int	count_hd(char *str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
			{
				nb++;
				i++;
			}
		}
		i++;
	}
	return (nb);
}

static void	ft_getdelims(char *str, t_here *here)
{
	int		nb;
	int		i;

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

static
char	*openfileshd(int index, t_here *here)
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

static
void    exit_hd(int sig)
{
    t_data    *data;
    int        i;

    data = starton();
	ft_printf("data->here : %p\n", data->here);
    if (sig == SIGINT)
    {
        ft_putchar_fd('\n', 2);
        i = -1;
        while (++i < data -> nb_here)
        {
			ft_printf("is ok : %s\n",data->here[i].delim);
			close(data->here[i].pipe[1]);
			close(data->here[i].pipe[0]);
            if (data->here[i].delim != NULL)
                ft_free((void **)& data->here[i].delim);
        }
		free_all(2, 2, &data->str, &data->here, data->path, data->env);
        exit(130);
    }
}

t_here	*here_doc(t_data *data, char *str)
{
	t_here *here;
	int nbhere;
	int i;
	char **tab;
	char **delimiter;
	int r;

	data->nb_here = count_hd(str);
	data->here = ft_calloc(sizeof(t_here), data->nb_here);
	ft_getdelims(str, data->here);
	signal(SIGINT, SIG_IGN);
	pid_t pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &exit_hd);
		i = -1;
		while (++i < data->nb_here)
			openfileshd(i, data->here);
		freestruct(data);
		free_all(2, 2, &data->here, &str, data->env, data->path);
		exit(1);
	}
	else if (pid > 0)
	{
		i = -1;
		while (++i < data->nb_here)
			close(data->here[i].pipe[1]);
	}
	signal(SIGINT, &ctrlc);
	waitpid(pid, &r, 0);
	return (here);
}