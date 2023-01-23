/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 03:53:43 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/23 00:37:55 by mgamil           ###   ########.fr       */
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
	ft_free((void **)&str);
	ft_freetab(tab);
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
	if (!*str || !ft_strcmp(str, "exit"))
	{
		data->status = 0;
		return (2);
	}
	return (0);
}

int	exec(t_data *data)
{
	char	*str;
	int		fd;
	t_btree	*tree;

	while (1)
	{
		str = prompt(data);
		fd = open("history.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
		ft_putendl_fd(str, fd);
		close(fd);
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
		here_doc(data, str);
		str = ft_expand(str, data->env);
		tree = get_tree(str, data->env, data);
		ft_free((void **)&str);
		if (tree)
		{
			print_tree(tree, 2);
			exec_tree(tree);
			free_tree(tree);
		}
		free_all(0, 2, data->filename, data->here_docs);
	}
	free_all(2, 2, &data->prompt, &str, data->path, data->env);
	ft_printf("exit\n");
	// ft_free((void **)&data->prompt);
	rl_clear_history();
	// ft_free((void **)&str);
	// ft_freetab(data->path);
	// ft_freetab(data->env);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
	// if(!isatty(STDIN_FILENO))
	// 	data.tty = 1;
	ft_memset(&data, 0, sizeof(t_data));
	data.prev_pipes = -1;
	data.env = ft_copy_tab(env);
	exec(&data);
	exit(data.status);
}

/*

tab[0] = <			// REDIR
tab[1] = Makefile	// FILE
tab[2] = cat		// CMD
tab[3] = |			// PIPE
tab[4] = grep		// CMD
tab[5] = " 'lol"	// ARG
tab[6] = |			// PIPE
tab[7] = ls			// CMD
tab[8] = -l			// ARG
tab[9] = >			// REDIR
tab[10] = outfile	// FILE


	LISTE CHAINEE

exemple 1:
0				1	2	3				4	5		6
<	Makefile	cat	|	grep	" 'lol"	|	ls	-l	>>	outfile

		TYPE	NAME	OPTS
<		1		<		{"Makefile", NULL}
cat		0		cat		{"cat", NULL}
|		-1		|		{NULL}
grep	0		grep	{"grep", " 'lol", NULL}
|		-1		|		{NULL}
ls		0		ls		{"ls", {"-l"}, NULL};
>>		4		>>		{"outfile"}

exemple 2:
0		1
<< stop > file1

		TYPE	NAME	OPTS
<<		2		<<		{"stop", NULL}
>>		4		>>		{"file1", NULL}


exemple 3:
0		1				2	3			4			5	6
ls	-R	>	/dev/stdout	|	<	infile	>	outfile	|	wc	-w

		TYPE	NAME	OPTS
ls		0		ls		{"ls", "-R", NULL}
>		3		>		{"/dev/stdout", NULL}
|		-1		|		{NULL}
<		1		<		{"infile", NULL}
>		3		>		{"outfile", NULL}
|		-1		|		{NULL}
wc		0		wc		{"wc", "-w", NULL}


*/

/*
 
(	(	(a	|	b)	&&	c)	||	d)	|	(e	&&	f)
						|
			||					&&
		&&		d			e		f
	|		c
a		b


(	(	(a	|	b)	&&	c)	||	d)	|	(	(	(a	|	b)	&&	c)	||	d)
									|
			||											||
		&&		d									&&		d
	|		c									|		c
a		b									a		b



*/

/*

tab[i]
si		i = 0 et que c pas une redirection === commande
si i > 0 et que c pas une redirection === argument
sinon redirection

*/

/*


10 animaux
56 croq
1 chien = 6 croq
1 chat =  5 croq


56 = 6x + 5y





*/

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