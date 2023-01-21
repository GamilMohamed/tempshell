/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 03:07:10 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/20 06:11:27 by mgamil           ###   ########.fr       */
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
	// ft_printf("len delimiter=%i\n", r);
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
	{
		// ft_printf("->%c\n", str[i]);
		new[r++] = str[i++];
	}
	new[r] = 0;
	// printf("new=%s\n", new);
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

static char	**ft_getdelims(char *str)
{
	int		nb;
	int		i;
	char	**tab;

	tab = malloc(sizeof(char *) * (count_hd(str) + 1));
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
				tab[nb++] = get_word(&str[i]);
			}
		}
		i++;
	}
	tab[nb] = 0;
	// ft_printtab(tab);
	return (tab);
}

static char	*openfiles(int index, t_data *data)
{
	char	*s;
	int		fd;

	fd = open(data->filename[index], O_RDWR | O_CREAT | O_TRUNC, 0666);
	while (1)
	{
		s = readline(">");
		if (!s || !ft_strcmp(s, data->here_docs[index]))
			break ;
		ft_putendl_fd(s, fd);
		free(s);
		ft_printf("JE SUIS PASSE PAR LA\n");
	}
	close(fd);
	// ft_printf("fd=%i\n", fd);
	return (NULL);
}

static char	**ft_getnames(t_data *data, char *str, int max)
{
	int		i;
	char	*name;
	char	**tab;

	tab = malloc(sizeof(char *) * (max + 1));
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

char	*here_doc(t_data *data, char *str)
{
	int nbhere;
	int i;
	char **tab;
	char **delimiter;

	int r;
	data->here_docs = ft_getdelims(str);
	nbhere = count_hd(str);
	data->filename = ft_getnames(data, str, nbhere);
	if (!nbhere)
		return (NULL);
	signal(SIGINT, SIG_IGN);
	// signal(SIGINT, & ctrlc);
	pid_t pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, &antislash);
		i = -1;
		while (++i < nbhere)
		{
			openfiles(i, data);
			free(data->filename[i]);
		}
		free(data->filename);
		ft_freetab(data->here_docs);
		ft_freetab(data->env);
		exit(1);
	}
	else if (pid > 0)
	{
	}
	signal(SIGINT, &ctrlc);
	// ft_printf("here_doc made = %i\n", nbhere);
	waitpid(pid, &r, 0);
	return (str);
}