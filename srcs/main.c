/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 03:53:43 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/24 22:18:03 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(t_data *data)
{
	char	*str;
	char	prompt[PATH_MAX];
	char	**tab;
	int		count;

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
	free_all(1, 1, &str, tab);
	return (readline(prompt));
}

// char	*ft_quote(char *str)
// {
// 	int		i;
// 	int		r;
// 	int		quote;
// 	char	*new;
// 	char	*ret;

// 	i = 0;
// 	r = 0;
// 	new = malloc(ft_strlen(str) + 1);
// 	while (str[i])
// 	{
// 		while (str[i] && str[i] == SQUOTE || str[i] == DQUOTE)
// 		{
// 			quote = str[i++];
// 			// new[r++] = ' ';
// 			while (str[i] && str[i] != quote)
// 			{
// 				if (ft_strchr("\t\v\n >|<", str[i]))
// 					str[i] = -str[i];
// 				new[r++] = str[i++];	
// 			}
// 			i++;
// 		}
// 		if (!str[i])
// 			break ;
// 		new[r++] = str[i++];
// 	}
// 	new[r] = 0;
// 	ret = ft_strdup(new);
// 	free_all(2, 0, &new, &str);
// 	return (ret);
// }

int	syntax(t_data *data, char *str)
{
	if (!*str)
		return (1);
	if (checksyntax(str) || checkquotes(str) || !parsing(str))
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

void	pre_exec(t_data *data)
{
	t_btree	*tree;
	t_btree	*temp;
	int		i;

	data->str = ft_expand(data->str, data->env);
	here_doc(data, data->str);
	tree = get_tree(data->str, data->env, data);
	ft_free((void **)&data->str);
	if (tree)
	{
		temp = tree;
		// print_tree(tree, 2);
		exec_tree(tree, temp);
		free_tree(tree);
	}
	i = -1;
	while (++i < data->nb_here)
		close(data->here[i].pipe[0]);
	freestruct(data);
	ft_freetab(data->path);
	ft_getenv(data->env, data);
}

int	exec(t_data *data)
{
	t_here	here;

	while (1)
	{
		data->str = prompt(data);
		if (!data->str)
			break ;
		add_history(data->str);
		if (syntax(data, data->str) == 1)
			continue ;
		if (syntax(data, data->str) == 2)
			break ;
		if (!ft_strcmp(data->str, "echo $?"))
		{
			printf("%i\n", data->status);
			continue ;
		}
		data->here = &here;
		pre_exec(data);
	}
	free_all(1, 2, &data->str, data->path, data->env);
	ft_printf("exit\n");
	rl_clear_history();
	return (0);
}

int	init(t_data *data, char **env)
{
	ft_memset(data, 0, sizeof(t_data));
	data->prev_pipes = -1;
	data->env = ft_copy_tab(env);
	ft_getenv(data->env, data);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = starton();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
	init(data, env);
	exec(data);
	exit(data->status);
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