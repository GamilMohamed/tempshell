/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 03:07:10 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/23 07:49:13 by mgamil           ###   ########.fr       */
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
	while (str[i] && !ft_isspace(str[i]))
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
	while (str[i] && !ft_isspace(str[i]))
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

static char	**ft_getdelims(char *str, t_here *here)
{
	int		nb;
	int		i;
	char	**tab;

	here->here_docs = malloc(sizeof(char *) * (here->nb_here + 1));
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
				here->here_docs[nb++] = get_word(&str[i]);
			}
		}
		i++;
	}
	here->here_docs[nb] = 0;
	return (tab);
}

static char	*openfileshd(int index, t_here *here)
{
	char	*s;
	int		fd;

	fd = open(here->filename[index], O_RDWR | O_CREAT | O_TRUNC, 0666);
	while (1)
	{
		s = readline(">");
		if (!s || !ft_strcmp(s, here->here_docs[index]))
			break ;
		ft_putendl_fd(s, fd);
		free(s);
	}
	close(fd);
	return (NULL);
}

static char	**ft_getnames(t_here *here, char *str, int max)
{
	int		i;
	char	*name;
	char	**tab;

	tab = ft_calloc(sizeof(char *), (max + 1));
	i = -1;
	while (++i < max)
	{
		name = ft_itoa(i);
		tab[i] = ft_strjoin("./here_doc/", name);
		free(name);
	}
	tab[i] = 0;
	return (tab);
}

char	*here_doc(t_here *here, char *str)
{
	int nbhere;
	int i;
	char **tab;
	char **delimiter;
	int r;

	here->nb_here = count_hd(str);
	ft_getdelims(str, here);
	here->filename = ft_getnames(here, str, here->nb_here);
	if (!here->nb_here)
		return (NULL);
	signal(SIGINT, SIG_IGN);
	// signal(SIGINT, & ctrlc);
	pid_t pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &antislash);
		i = -1;
		while (++i < here->nb_here)
		{
			openfileshd(i, here);
			free(here->filename[i]);
		}
		free(here->filename);
		ft_freetab(here->here_docs);
		// ft_freetab(env);
		exit(1);
	}
	else if (pid > 0)
	{
	}
	signal(SIGINT, &ctrlc);
	waitpid(pid, &r, 0);
	return (str);
}