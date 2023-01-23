/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 03:53:43 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/23 08:07:25 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(t_data *data)
{
	char	*str;
	char	prompt[PATH_MAX];
	char	**tab;
	int		count;

	data->here->hd = 0;
	str = builtin_pwd(NULL);
	tab = ft_split(str, '/');
	count = ft_countdelim(str, '/');
	if (data->status)
		ft_strcpy(prompt, RED);
	else
		ft_strcpy(prompt, GREEN);
	if (count)
		ft_strcat(prompt, tab[count - 1]);
	else
		ft_strcat(prompt, str);
	ft_strcat(prompt, "\001\033[0m\002:");
	free_all(1, 1, & str, tab);
	return (readline(prompt));
}

int	syntax(t_data *data, char *str)
{
	if (!*str)
		return (1);
	if (checksyntax(str) || checkquotes(str))
	{
		data->status = 2;
		return (1);
	}
	if (!ft_strcmp(str, "exit"))
	{
		data->status = 0;
		return (2);
	}
	return (0);
}

int	exec(t_data *data)
{
	char	*str;
	t_btree	*tree;

	while (1)
	{
		str = prompt(data);
		if (!str)
			break ;
		add_history(str);
		if (syntax(data, str) == 1)
			continue ;
		if (syntax(data, str) == 2)
			break ;
		if (!ft_strcmp(str, "echo $?"))
		{
			printf("%i\n", data->status);
			continue ;
		}
		here_doc(data->here, str);
		str = ft_expand(str, data->env);
		tree = get_tree(str, data->env, data);
		ft_free((void **)&str);
		if (tree)
		{
			print_tree(tree, 2);
			exec_tree(tree);
			free_tree(tree);
		}
		free_all(0, 2, data->here->filename, data->here->here_docs);
	}
	free_all(1, 2, &str, data->path, data->env);
	ft_printf("exit\n");
	clear_history();
	return (0);
}

int	init(t_data *data, t_here *here, char **env)
{
	ft_memset(data, 0, sizeof(t_data));
	data->prev_pipes = -1;
	data->here = here;
	data->here->hd = 0;
	data->env = ft_copy_tab(env);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_here	here;

	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
	init(& data, & here, env);
	exec(& data);
	exit(data.status);
}

/*
MINISHELLL:cat | cat | cat | cat | ls
[cat | cat | cat | cat | ls]
nbcmd=5
4|5|-1
5|6|4
4|6|5
5|6|4
4|6|5
append	history.txt  includes  libft.a			liblkriefft.a  minishell  out   out2  out4		outside  srcs
gab	ignore.txt   libft     liblkriefft  Makefile		objs       out1  out3  outfile  pipex




MINISHELLL:
*/