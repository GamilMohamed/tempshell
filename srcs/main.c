/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 03:53:43 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/17 02:02:43 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_puterror(int flag)
{
	if (flag & FAILED_MALLOC)
		ft_putstr_fd("Malloc failed\n", STDERR_FILENO);
	return (NULL);
}

void	prompt(t_data *data)
{
	char		*str;
	char		**tab;
	int			count;
	str = builtin_pwd(NULL);
	tab = ft_split(str, '/');
	count = ft_countdelim(str, '/');
	if (data->status)
		data->prompt = ft_strdup(RED);
	else
		data->prompt = ft_strdup(GREEN);
	if (count)
		data->prompt = ft_realloc(data->prompt, tab[count - 1]);
	else
		data->prompt = ft_realloc(data->prompt, str);
	data->prompt = ft_realloc(data->prompt, "\001\033[0m\002:");
	ft_free((void **)& 	str);
	ft_freetab(tab);
}

int	exec(char **env, t_data *data)
{
	char	*str;
	int		fd;
	t_btree	*tree;

	env = ft_copy_tab(env);
	while (1)
	{
		prompt(data);
		str = readline(data->prompt);
		ft_free((void **)& data->prompt);
		fd = open("history.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
		ft_putendl_fd(str, fd);
		add_history(str);
		close(fd);
		if (!str)
			break ;
		if (!ft_strcmp(str, "echo $?"))
		{
			printf("%i\n", data->status);
			continue ;
		}
		if (checkquotes(str) || checksyntax(str))
			continue ;
		str = ft_expand(str, env);
		if (ft_builtin(str, env, &env))
			continue ;
		if (!str || !*str || !ft_strcmp(str, "exit"))
			break ;
		tree = get_tree(str, env, data);
		ft_free((void **)&str);
		if (tree)
		{
			print_tree(tree, 2);
			exec_tree(tree, STDIN_FILENO, STDOUT_FILENO);
			free_tree(tree);
		}
		// ft_printf("FIN EXECUTION PREMIeRE CMD\n");
		// ft_infix(tree);
	}
	ft_free((void **)& data->prompt);
	rl_clear_history();
	ft_free((void **)& str);
	ft_freetab(data->path);
	ft_freetab(env);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	(void)ac;
	(void)av;
	
	signal(SIGQUIT, SIG_IGN);
	ft_memset(&data, 0, sizeof(t_data));
	data.env = env;
	data.prev_pipes = -1;
	exec(env, &data);
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
append	history.txt  includes  libft.a			liblkriefft.a  minishell  out   out2  out4	   outside  srcs
gab	ignore.txt   libft     liblkriefft  Makefile		objs       out1  out3  outfile  pipex




MINISHELLL:
*/